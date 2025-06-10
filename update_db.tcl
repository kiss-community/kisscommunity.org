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

sqlite3 db db.sqlite
db eval {
	DROP TABLE IF EXISTS files;
	CREATE VIRTUAL TABLE IF NOT EXISTS files USING fts5(path, content, tokenize = "porter unicode61 tokenchars '&;'")
}

set files [split [exec find wiki -name index.md -o -name index.txt] \n]
set dirs {}
foreach path $files {
	set dir [file dirname $path]
	lappend dirs $dir
}
# remove duplicates (eg if both index.txt and index.md in same dir)
set dirs [lsort -unique $dirs]

foreach dir $dirs {
	set path [file join $dir index.md]
	set md 1
	if {[file exists $path] != 1} {
		set path [file join $dir index.txt]
		set md 0
	}
	set fh [open $path r]
	set content [read $fh]
	set content [removespaces $content]
	if $md {
		# txts should already have chars escaped.
		set content [htmlize $content]
	}
	close $fh

	# ./wiki/foo/bar -> /foo/bar
	set path [file join / {*}[lreplace [file split $dir] 0 0]]
	db eval {INSERT INTO files VALUES($path, $content)}
}

db close
