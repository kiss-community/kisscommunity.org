.POSIX:

CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -static -s

all: html db.sqlite

html: build-page smu/smu htmlclean
	find wiki -type d -exec sh -ec 'PATH="$$PWD/smu:$$PATH" ./build-page "$$0" >$$0/index.html' {} \;

htmlclean:
	-find wiki -type f -name \*.html -exec rm {} \;
	-find wiki -type d -exec rmdir {} \; 2>/dev/null

db.sqlite:
	tclsh update_db.tcl

build-page: build-page.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ build-page.c

smu/smu:
	cd smu; patch -p1 < ../0001-support-tagged-links.patch
	cd smu; $(MAKE)

clean:
	rm -f build-page

.PHONY: all clean html htmlclean db.sqlite
