Published **4th Nov 2019** by [Dylan
Araps](https://github.com/dylanaraps).

# I've gone to great lengths for this silence

I've spent a lot of time ensuring this website remains small, simple
and fast. To quote [Futurama](https://en.wikipedia.org/wiki/Futurama)
"When You Do Things Right, People Won't Be Sure You've Done Anything at
All". I've gone to great lengths for this silence.

## The generation process

This website is statically generated from a [simple shell
script](https://github.com/kiss-community/website/blob/master/make)
using [pandoc](https://pandoc.org/), with every page written in basic
[markdown](https://en.wikipedia.org/wiki/Markdown).

As this site contains near zero images, I optimize each image by hand
using [Compress or Die](https://compress-or-die.com/) and load a `webp`
or `jpg` image depending on browser support.

Every page shares the same CSS style-sheet and I also minify this by
hand. I've found that a lot of CSS minifiers actually *increase* the
file size.

## Why is it fast?

Every page is only **a single HTTP request**\*. To achieve this, each
page is entirely self-contained. A page is comprised of the HTML with
the entirety of the CSS inlined in `<style>` tags.

As an example, the end result is a grand total of **3.0KB** for
[k1ss.org](/) all contained in a single HTTP request.

**\*** With the exception of the Screenshots page.

## Analytics

**They don't belong here.** I don't know how many people visit this
website nor do I know anything about you!

Besides, it'd be unfair for me to browse the web with [Ublock
Origin](https://github.com/gorhill/uBlock) plus JavaScript disabled and
then **track you** on my site.

## Removing the favicon

The favicon has also been put to rest. This isn't as simple as not
setting one! All of the major browsers will request a favicon **even if
one hasn't been set**.

The workaround is to simply inline a favicon in each page. Through a lot
of tinkering I have found the smallest inline favicon which ensures
**zero HTTP requests**.

Behold: `<link href=data:, rel=icon>`

**Update**

You may have noticed this site now has a favicon. You may have also
noticed that each page is still only a single web request!

Through firing up [Grafx2](http://grafx2.chez.com/) (*a pixel art
editor*) and various optimization techniques I have created a simple
favicon for the site.

This is a simple 4 color favicon (*1 color being the transparent
background*) in `gif` format and
[base64](https://en.wikipedia.org/wiki/Base64) encoded to be embeddable
in HTML.

    <link href="data:image/gif;base64,R0lGODlhEAAQAPH/AAAAAP8AAP8AN////yH5BAUAAAQALAAAAAAQABAAAAM2SLrc/jA+QBUFM2iqA2bAMHSktwCCWJIYEIyvKLOuJt+wV69ry5cfwu7WCVp2RSPoUpE4n4sEADs=" rel=icon>

I don't know if I'll keep this around or not, time will tell.
Regardless, this was a fun excercise!

## Fonts

No external fonts are in use. The body's `font-family` is set to
`sans-serif` and will use whatever font is browser's default.

## JavaScript

No JavaScript is used anywhere on the website. It isn't needed and is
therefore omitted. Each page is strictly a document comprised of
information.

## HTML

The HTML is minified using a single `sed` command! I'll leave the
dissection of the command to you, the reader. It's a fun exercise as
`sed` is more powerful than people realise.

Behold: `sed ':a;N;$!ba;s|>\s*<|><|g'`

## CSS

As mentioned above the CSS is inlined in each page inside `<style>` tags
and it is minified by hand. I use various techniques to reduce its size.

All unnecessary white-space is removed (`ul{display:block}`). This is
arguably the easiest minification step to do yourself.

Shorthand rules are used wherever possible (`font:` in place of `font-*`
and `background:` in place of `background-*`). A lot of these are
circumstantial.

Classes are avoided and IDs are instead used. This is actually a HTML
minification technique (`id=a` vs `class=a`). It's even better if
you're able to stick strictly to styling HTML tags!

All colors used on this site have a 3 character long shorthand. This
enables the use of `#fff` instead of `#ffffff`. This is really easy to
do if [Web Safe
Colors](https://en.wikipedia.org/wiki/Web_colors#Web-safe_colors) are
used.

The CSS on this website is still far from perfect however! The hardest
minification technique (*at least for me*) is the **removal** of unused,
unneeded or unapplied CSS rules. I'm still having fun with this one.

## Conclusion

I will continue to chip away the source of this site, however
diminishing the end results may be. This is just who I am. If there's
wiggle room, I'll wiggle.

The full un-generated source for this website can be found here:
<https://github.com/kiss-community/website>

## Get in touch

If you have any further questions, feel free to [contact
me](/pages/contact).

### Legal stuff

The registered trademark Linux® is used pursuant to a sublicense from
the Linux Foundation, the exclusive licensee of Linus Torvalds, owner of
the mark on a world­wide basis.

© [Dylan Araps](https://github.com/dylanaraps) 2019-2020
