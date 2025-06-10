#!/usr/bin/awk -f
# Run this twice (awk -f convert_links.awk index.txt index.txt) to convert bibliography style links to inline links.

function esc(str,	 out, i, c) {
	out = ""
	for (i = 1; i <= length(str); i++) {
		c = substr(str, i, 1)
		if (c ~ /[][(){}.^$*+?|\\]/)
			out = out "\\" c
		else
			out = out c
	}
	return out
}
NR==FNR && /^\[[0-9]*\]/ {
	w=$1;
	$1="";
	sub(/^ /, "");
	saved[w]=$0;
}
NR != FNR && $0 !~ /^\[[0-9]*\]/ {
	for (k in saved) {
		ek = esc(k)
		gsub(ek, "[" k "](" saved[k] ")")
	}
	print
}

