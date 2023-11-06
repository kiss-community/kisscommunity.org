#!/usr/local/bin/tclsh8.6
# This script is run in the post-receive hook.

package require sqlite3

proc htmlize str {
	string map {< &lt; > &gt; \x22 &quot; \x26 &amp; } $str
}

proc removespaces {content} {
	set content [string map {__ {} ++ {} == {} -- {}} $content]
	regsub -all {[ \t\n]+} $content { }
}

set files [split [exec find wiki -name *.md -o -name *.txt] \n]

sqlite3 db db.sqlite
db eval {
	DROP TABLE IF EXISTS files;
	CREATE VIRTUAL TABLE IF NOT EXISTS files USING fts5(path, content, tokenize = "porter unicode61 tokenchars '&;'")
}

foreach path $files {
	set fh [open $path r]
	set content [read $fh]
	set content [removespaces $content]
	if {[string match *.md $path]} {
		# txts should already have chars escaped.
		set content [htmlize $content]
	}
	close $fh

	# ./wiki/foo/bar/index.xxx -> /foo/bar
	set path [file join / {*}[lreplace [lreplace [file split $path] 0 0] end end]]
	# remove duplicates (eg if both index.txt and index.md in same dir)
	set path [lsort -unique $path]
	db eval {INSERT INTO files VALUES($path, $content)}
}

db close
