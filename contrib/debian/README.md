
Debian
====================
This directory contains files used to package phtevencoind/phtevencoin-qt
for Debian-based Linux systems. If you compile phtevencoind/phtevencoin-qt yourself, there are some useful files here.

## phtevencoin: URI support ##


phtevencoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install phtevencoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your phtevencoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/phtevencoin128.png` to `/usr/share/pixmaps`

phtevencoin-qt.protocol (KDE)

