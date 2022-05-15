/* process Markdown (based on smu code), but only output links */
#include <sys/types.h>

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __OpenBSD__
#include <unistd.h>
#else
#define pledge(a,b) 0
#endif

#define READ_BUF_SIZ 16384
#define LEN(x)  sizeof(x)/sizeof(x[0])
#define ADDC(b,i)  if (i % READ_BUF_SIZ == 0) { b = realloc(b, (i + READ_BUF_SIZ)); if (!b) eprint("realloc:"); } b[i]

typedef int (*Parser)(const char *, const char *, int);
typedef struct {
	char *search;
	int process;
	char *before, *after;
} Tag;

static int dolineprefix(const char *begin, const char *end, int newblock);/* Parser for line prefix tags */
static int dolink(const char *begin, const char *end, int newblock);      /* Parser for links and images */
static int dolist(const char *begin, const char *end, int newblock);      /* Parser for lists */
static int doparagraph(const char *begin, const char *end, int newblock); /* Parser for paragraphs */
static int doshortlink(const char *begin, const char *end, int newblock); /* Parser for links and images */
static int dosurround(const char *begin, const char *end, int newblock);  /* Parser for surrounding tags */
static int dounderline(const char *begin, const char *end, int newblock); /* Parser for underline tags */
static void *ereallocz(void *p, size_t size);
static void hprint(const char *begin, const char *end);                   /* escapes HTML and prints it to output */
static void process(const char *begin, const char *end, int newblock);    /* Processes range between begin and end. */

/* list of parsers */
static Parser parsers[] = {
	dounderline, dolineprefix, dolist, doparagraph, dosurround, dolink, doshortlink,
};
 
static Tag lineprefix[] = {
	{ "   ",	0,	"<pre><code>", "</code></pre>" },
	{ "\t",		0,	"<pre><code>", "</code></pre>" },
	{ "> ",		2,	"<blockquote>",	"</blockquote>" },
	{ "###### ",	1,	"<h6>",		"</h6>" },
	{ "##### ",	1,	"<h5>",		"</h5>" },
	{ "#### ",	1,	"<h4>",		"</h4>" },
	{ "### ",	1,	"<h3>",		"</h3>" },
	{ "## ",	1,	"<h2>",		"</h2>" },
	{ "# ",		1,	"<h1>",		"</h1>" },
	{ "- - -\n",	1,	"<hr/>",	""},
};

static Tag underline[] = {
	{ "=",		1,	"<h1>",		"</h1>\n" },
	{ "-",		1,	"<h2>",		"</h2>\n" },
};

static Tag surround[] = {
	{ "``",		0,	"<code>",	"</code>" },
	{ "`",		0,	"<code>",	"</code>" },
	{ "___",	1,	"<b><i>",	"</i></b>" },
	{ "***",	1,	"<b><i>",	"</i></b>" },
	{ "__",		1,	"<b>",		"</b>" },
	{ "**",		1,	"<b>",		"</b>" },
	{ "_",		1,	"<i>",		"</i>" },
	{ "*",		1,	"<i>",		"</i>" },
};

void
eprint(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	if (format[0] && format[strlen(format) - 1] == ':')
		fputs(strerror(errno), stderr);
	fputc('\n', stderr);
	exit(1);
}

int
dolineprefix(const char *begin, const char *end, int newblock)
{
	unsigned int i, j, l;
	char *buffer;
	const char *p;

	if (newblock)
		p = begin;
	else if (*begin == '\n')
		p = begin + 1;
	else
		return 0;
	for (i = 0; i < LEN(lineprefix); i++) {
		l = strlen(lineprefix[i].search);
		if (end - p < l)
			continue;
		if (strncmp(lineprefix[i].search, p, l))
			continue;
		if (lineprefix[i].search[l-1] == '\n') {
			return l;
		}
		if (!(buffer = malloc(BUFSIZ)))
			eprint("malloc:");
		buffer[0] = '\0';

		for (j = 0, p += l; p < end; p++, j++) {
			ADDC(buffer, j) = *p;
			if (*p == '\n' && p + l < end) {
				if (strncmp(lineprefix[i].search, p + 1, l) != 0)
					break;
				p += l;
			}
		}

		ADDC(buffer, j) = '\0';
		if (lineprefix[i].process)
			process(buffer, buffer + strlen(buffer), lineprefix[i].process >= 2);
		free(buffer);
		return -(p - begin);
	}
	return 0;
}

int
dolink(const char *begin, const char *end, int newblock)
{
	int img, len, sep;
	const char *desc, *link, *p, *q, *descend, *linkend;
	const char *title = NULL, *titleend = NULL;

	if (*begin == '[')
		img = 0;
	else if (strncmp(begin, "![", 2) == 0)
		img = 1;
	else
		return 0;
	p = desc = begin + 1 + img;
	if (!(p = strstr(desc, "](")) || p > end)
		return 0;
	for (q = strstr(desc, "!["); q && q < end && q < p; q = strstr(q + 1, "!["))
		if (!(p = strstr(p + 1, "](")) || p > end)
			return 0;
	descend = p;
	link = p + 2;
	if (!(q = strchr(link, ')')) || q > end)
		return 0;
	if ((p = strpbrk(link, "\"'")) && p < end && q > p) {
		sep = p[0]; /* separator: can be " or ' */
		title = p + 1;
		/* strip trailing whitespace */
		for (linkend = p; linkend > link && isspace(*(linkend - 1)); linkend--)
			;
		if (!(p = strchr(title, sep)) || q > end || p > q)
			return 0;
		titleend = p;
		len = p + 2 - begin;
	}
	else {
		linkend = q;
		len = q + 1 - begin;
	}
	if (img) {
		fwrite(link, 1, linkend - link, stdout);
		fputs("\n", stdout);
	}
	else {
		fwrite(link, 1, linkend - link, stdout);
		fputs("\n", stdout);

		process(desc, descend, 0);
	}
	return len;
}

int
dolist(const char *begin, const char *end, int newblock)
{
	unsigned int i, j, indent, run, ul, isblock;
	const char *p, *q;
	char *buffer = NULL;

	isblock = 0;
	if (newblock)
		p = begin;
	else if (*begin == '\n')
		p = begin + 1;
	else
		return 0;
	q = p;
	if (*p == '-' || *p == '*' || *p == '+')
		ul = 1;
	else {
		ul = 0;
		for (; p < end && *p >= '0' && *p <= '9'; p++)
			;
		if (p >= end || *p != '.')
			return 0;
	}
	p++;
	if (p >= end || !(*p == ' ' || *p == '\t'))
		return 0;
	for (p++; p != end && (*p == ' ' || *p == '\t'); p++)
		;
	indent = p - q;
	buffer = ereallocz(buffer, BUFSIZ);
	run = 1;
	for (; p < end && run; p++) {
		for (i = 0; p < end && run; p++, i++) {
			if (*p == '\n') {
				if (p + 1 == end)
					break;
				else if (p[1] == '\n') {
					p++;
					ADDC(buffer, i) = '\n';
					i++;
					run = 0;
					isblock++;
				}
				q = p + 1;
				j = 0;
				if (ul && (*q == '-' || *q == '*' || *q == '+'))
					j = 1;
				else if (!ul) {
					for (; q + j != end && q[j] >= '0' && q[j] <= '9' && j < indent; j++)
						;
					if (q + j == end)
						break;
					if (j > 0 && q[j] == '.')
						j++;
					else
						j = 0;
				}
				if (q + indent < end)
					for (; (q[j] == ' ' || q[j] == '\t') && j < indent; j++)
						;
				if (j == indent) {
					ADDC(buffer, i) = '\n';
					i++;
					p += indent;
					run = 1;
					if (*q == ' ' || *q == '\t')
						p++;
					else
						break;
				}
			}
			ADDC(buffer, i) = *p;
		}
		ADDC(buffer, i) = '\0';
		process(buffer, buffer + i, isblock > 1 || (isblock == 1 && run));
	}
	free(buffer);
	p--;
	while (*(--p) == '\n')
		;
	return -(p - begin + 1);
}

int
doparagraph(const char *begin, const char *end, int newblock)
{
	const char *p;

	if (!newblock)
		return 0;
	p = strstr(begin, "\n\n");
	if (!p || p > end)
		p = end;
	if (p == begin)
		return 0;
	process(begin, p, 0);
	return -(p - begin);
}

int
doshortlink(const char *begin, const char *end, int newblock)
{
	const char *p;
	int ismail = 0;

	if (*begin != '<')
		return 0;
	for (p = begin + 1; p != end; p++) {
		switch (*p) {
		case ' ':
		case '\t':
		case '\n':
			return 0;
		case '#':
		case ':':
			ismail = -1;
			break;
		case '@':
			if (ismail == 0)
				ismail = 1;
			break;
		case '>':
			if (ismail == 0)
				return 0;
			if (ismail != 1) {
				fwrite(begin + 1, 1, p - begin - 1, stdout);
				fputs("\n", stdout);
			}
			return p - begin + 1;
		}
	}
	return 0;
}

int
dosurround(const char *begin, const char *end, int newblock)
{
	unsigned int i, l;
	const char *p, *start, *stop;

	for (i = 0; i < LEN(surround); i++) {
		l = strlen(surround[i].search);
		if (end - begin < 2*l || strncmp(begin, surround[i].search, l) != 0)
			continue;
		start = begin + l;
		p = start - 1;
		do {
			stop = p;
			p = strstr(p + 1, surround[i].search);
		} while (p && p[-1] == '\\');
		if (p && p[-1] != '\\')
			stop = p;
		if (!stop || stop < start || stop >= end)
			continue;
		if (surround[i].process)
			process(start, stop, 0);
		else
			hprint(start, stop);
		return stop - begin + l;
	}
	return 0;
}

int
dounderline(const char *begin, const char *end, int newblock)
{
	unsigned int i, j, l;
	const char *p;

	if (!newblock)
		return 0;
	p = begin;
	for (l = 0; p + l != end && p[l] != '\n'; l++)
		;
	p += l + 1;
	if (l == 0)
		return 0;
	for (i = 0; i < LEN(underline); i++) {
		for (j = 0; p + j != end && p[j] != '\n' && p[j] == underline[i].search[0]; j++)
			;
		if (j >= l) {
			if (underline[i].process)
				process(begin, begin + l, 0);
			else
				hprint(begin, begin + l);
			return -(j + p - begin);
		}
	}
	return 0;
}

void *
ereallocz(void *p, size_t size)
{
	if (!(p = realloc(p, size)))
		eprint("realloc: could not allocate %u bytes:", size);
	return p;
}

void
hprint(const char *begin, const char *end)
{
}

void
process(const char *begin, const char *end, int newblock)
{
	const char *p, *q;
	int affected;
	unsigned int i;

	for (p = begin; p < end;) {
		if (newblock)
			while (*p == '\n')
				if (++p == end)
					return;
		affected = 0;
		for (i = 0; i < LEN(parsers) && !affected; i++)
			affected = parsers[i](p, end, newblock);
		p += abs(affected);
		if (!affected) {
			p++;
		}
		for (q = p; q != end && *q == '\n'; q++)
			;
		if (q == end)
			return;
		else if (p[0] == '\n' && p + 1 != end && p[1] == '\n')
			newblock = 1;
		else
			newblock = (affected < 0);
	}
}

int
main(int argc, char **argv)
{
	char *buffer;
	int s;
	size_t len, bsize;

	if (pledge("stdio", NULL) < 0)
		eprint("pledge:");

	bsize = 2 * READ_BUF_SIZ;
	buffer = ereallocz(NULL, bsize);
	len = 0;
	while ((s = fread(buffer + len, 1, READ_BUF_SIZ, stdin))) {
		len += s;
		if (READ_BUF_SIZ + len + 1 > bsize) {
			bsize += READ_BUF_SIZ;
			if (!(buffer = realloc(buffer, bsize)))
				eprint("realloc:");
		}
	}
	buffer[len] = '\0';
	process(buffer, buffer + len, 1);
	free(buffer);

	return 0;
}
