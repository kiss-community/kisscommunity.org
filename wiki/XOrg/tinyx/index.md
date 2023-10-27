# TinyX

Tinyx is a fork of `xorg-server` v1.2.0 and runs of off the framebuffer.

## Installation

Make sure you have the [ehawkvu/kiss-xorg](https://github.com/ehawkvu/kiss-xorg) repos in your $KISS_PATH.

``
	kiss build tinyx
``

###  sx

We also need `sx` to be able to launch tinyx.
Please refer to [sx](/XOrg/sx/) for how to setup sx.
We also need to make minor modifications to `sx`, to be able to launch tinyx.

``
	sed -i 's/Xorg/Xfbdev/';'s/-keeptty//' /usr/bin/sx
``

### Superkey

TinyX does **not** support the use of `Superkey` (also often refered to as Mod4).
This means if you have any packages which use keybindings which include the `Superkey`, they will have to be changed, else you'll be in for a bad time.
