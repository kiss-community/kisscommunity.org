#define _POSIX_C_SOURCE 200809L

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <dirent.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CONVERTER "smu", "-n"
#define LEN(x) (sizeof(x) / sizeof(x[0]))

char *html_header =
    "<!doctype html>\n"
    "<html>\n"
    "<head>\n"
    "\t<meta charset=\"utf-8\"/>\n"
    "\t<title>KISS Community Wiki</title>\n"
    "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"/style.css\"/>\n"
    "</head>\n";

char *html_nav_bar = "\t<span class=\"right\">\n"
                     "\t\t<a href=\"https://github.com/kiss-community\">Github</a>\n"
                     "\t\t<a href=\"https://kisslinux.org\">Official site</a>\n"
                     "\t</span>\n";

char *html_footer = "</html>\n";

void die_perror(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fputs(": ", stderr);
  perror(NULL);
  exit(1);
}

void die(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fputc('\n', stderr);
  exit(1);
}

char *xstrdup(const char *s) {
  char *p = strdup(s);

  if (!p)
    die_perror("strdup");

  return p;
}

int stat_isdir(const char *f) {
  struct stat s;

  if (stat(f, &s) == -1) {
    perror(f);
    return 0;
  }
  return S_ISDIR(s.st_mode);
}

int stat_isfile(const char *f) {
  struct stat s;

  if (stat(f, &s) == -1) {
    return 0;
  }
  return S_ISREG(s.st_mode);
}

int spawn_wait(char **argv) {
  int status;

  switch (fork()) {
  case 0:
    execvp(argv[0], argv);
    exit(126);
  case -1:
    return -1;
  }
  if (wait(&status) == -1)
    return -1;

  return WIFEXITED(status) ? WEXITSTATUS(status) ? -1 : 0 : -1;
}

void print_name(const char *name) {
  int c;

  for (; (c = *name); ++name)
    putchar((c == '_' || c == '-') ? ' ' : c);
}

void print_nav_bar(char *domain) {
  struct domain *d;

  puts("<div id=\"menu\">");
  puts("\t<a href=\"/\"><b>KISS Community Wiki</b></a>\n");

  fputs(html_nav_bar, stdout);
  puts("</div>");
}

int qsort_strcmp(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

int has_subdirs(char *this) {
  DIR *dp;
  struct dirent *de;
  char newdir[PATH_MAX];
  int dir;

  if ((dp = opendir(this ? this : ".")) == NULL)
    die_perror("opendir: %s", this ? this : ".");

  dir = 0;
  while (dir == 0 && (de = readdir(dp))) {
    if (de->d_name[0] == '.')
      continue;
    snprintf(newdir, sizeof(newdir), this ? "%2$s/%1$s" : "%s", de->d_name,
             this);
    if (stat_isdir(newdir))
      dir = 1;
  }
  closedir(dp);

  return dir;
}

void menu_panel(char *domain, char *page, char *this, int depth) {
  DIR *dp;
  struct dirent *de;
  char newdir[PATH_MAX];
  char *d_list[PATH_MAX], *d;
  size_t d_len, l;
  int i, highlight;

  if ((dp = opendir(this ? this : ".")) == NULL)
    die_perror("opendir: %s", this ? this : ".");

  d_len = 0;
  while (d_len < LEN(d_list) && (de = readdir(dp)))
    d_list[d_len++] = xstrdup(de->d_name);
  closedir(dp);

  qsort(d_list, d_len, sizeof *d_list, qsort_strcmp);

  for (l = 0; l < d_len; free(d_list[l++])) {
    d = d_list[l];
    if (*d == '.')
      continue;
    snprintf(newdir, sizeof(newdir), this ? "%2$s/%1$s" : "%s", d, this);
    if (!stat_isdir(newdir))
      continue;

    highlight = page && !strncmp(newdir, page, strlen(newdir)) &&
                strchr("/", page[strlen(newdir)]); /* / or NUL */

    for (i = 0; i < depth + 1; ++i)
      putchar('\t');
    fputs("<li>", stdout);
    if (highlight) {
      printf("<a href=\"/%s/\"><b>", newdir);
      print_name(d);
      fputs("/</b></a>", stdout);
    } else {
      printf("<a href=\"/%s/\">", newdir);
      print_name(d);
      fputs("/</a>", stdout);
    }

    if (highlight && has_subdirs(newdir)) {
      putchar('\n');
      for (i = 0; i < depth + 2; ++i)
        putchar('\t');
      puts("<ul>");
      menu_panel(domain, page, newdir, depth + 1);
      for (i = 0; i < depth + 2; ++i)
        putchar('\t');
      puts("</ul>");
      for (i = 0; i < depth + 1; ++i)
        putchar('\t');
    }
    puts("</li>");
  }
}

void print_menu_panel(char *domain, char *page) {
  fputs("<div id=\"nav\">\n\t<ul>\n\t<li>", stdout);
  if (!page)
    puts("<a href=\"/\"><b>Home</b></a></li>");
  else
    puts("<a href=\"/\">Home</a></li>");
  menu_panel(domain, page, NULL, 0);
  puts("\t</ul>");
  puts("</div>");
}

void print_content(char *domain, char *page) {
  char indexmd[PATH_MAX];
  char indextxt[PATH_MAX];
  char *argv[] = {CONVERTER, indexmd, NULL};

  snprintf(indexmd, sizeof(indexmd), page ? "%2$s/%1$s" : "%s", "index.md",
           page);
  snprintf(indextxt, sizeof(indextxt), page ? "%2$s/%1$s" : "%s", "index.txt",
           page);

  puts("<div id=\"main\">\n");
  if (stat_isfile(indexmd)) {
    fflush(stdout);
    if (spawn_wait(argv) == -1)
      die_perror("spawn: %s/%s/%s", domain, page, indexmd);
  } else if (stat_isfile(indextxt)) {
    puts("<pre>");
    FILE *fptr = fopen(indextxt, "r");
    char c = fgetc(fptr);
    while (c != EOF) {
      printf("%c", c);
      c = fgetc(fptr);
    }

    fclose(fptr);
    puts("</pre>");
  }

  puts("</div>\n");
}

void print_footer(void) { fputs(html_footer, stdout); }

int has_index(char *this) {
  DIR *dp;
  struct dirent *de;
  char newdir[PATH_MAX];
  int index;

  if ((dp = opendir(this ? this : ".")) == NULL)
    die_perror("opendir: %s", this ? this : ".");

  index = 0;
  while (index == 0 && (de = readdir(dp))) {
    if (de->d_name[0] == '.')
      continue;
    snprintf(newdir, sizeof(newdir), this ? "%2$s/%1$s" : "%s", de->d_name,
             this);
    if (stat_isfile(newdir) && strcmp(de->d_name, "index.md") == 0)
      index = 1;
  }
  closedir(dp);

  return index;
}

void usage(char *argv0) { die("usage: %s [-g] directory", argv0); }

int main(int argc, char *argv[]) {
  char *domain = NULL, *page;
  int i, j;

  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (domain)
        usage(argv[0]);
      domain = argv[i];
      continue;
    }
    for (j = 1; j < argv[i][j]; j++) {
      switch (argv[i][j]) {
      default:
        usage(argv[0]);
      }
    }
  }
  if (domain == NULL)
    usage(argv[0]);

  domain = xstrdup(domain);
  if ((page = strchr(domain, '/'))) {
    *page++ = '\0';
    if (strlen(page) == 0)
      page = NULL;
  }
  if (chdir(domain) == -1)
    die_perror("chdir: %s", domain);

  puts(html_header);
  print_nav_bar(domain);
  puts("<div id=\"content\">");
  print_menu_panel(domain, page);
  print_content(domain, page);
  puts("</div>\n");
  print_footer();

  return 0;
}
