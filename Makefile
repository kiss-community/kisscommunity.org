.POSIX:

CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -static -s

all: html

html: build-page smu/smu
	# first remove old html files and remove any empty dirs
	find wiki -type f -name \*.html -exec rm {} \;
	-find wiki -type d -exec rmdir {} \; 2>/dev/null
	find wiki -type d -exec sh -ec 'PATH="$$PWD/smu:$$PATH" ./build-page "$$0" >$$0/index.html' {} \;

build-page: build-page.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ build-page.c

smu/smu:
	cd smu; $(MAKE)

clean:
	rm -f build-page
