#!/usr/bin/awk -f
# For articles with only h2 and h3 as major and minor headings.
# If there is a ## Index already present, run with `awk -v major=-1`.
# You must manually move the index to the top.

BEGIN { li = 0 }

/^## / {
    printf("## [%%[%d.0]] %s\n", ++major, substr($0, 4))
    minor = 0
    labels[li,0] = major "." minor
    labels[li,1] = substr($0, 4)
    labels[li++,2] = 1
    next
}
/^### / {
    printf("### [%%[%d.%d]] %s\n", major, ++minor, substr($0, 5))
    labels[li,0] = major "." minor
    labels[li++,1] = substr($0, 5)
    next
}
{
    print
}

END {
    printf("\n## [%%[0.0]] Index\n\n")
    for (i=0; i < li; i++) {
        if (labels[i,2] != 1)
            printf("  ");
        printf("- [%s](#%s) %s\n", labels[i,0], labels[i,0], labels[i,1]);
    }
}
