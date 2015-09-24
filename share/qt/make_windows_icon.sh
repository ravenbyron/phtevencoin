#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/phtevencoin.png
ICON_DST=../../src/qt/res/icons/phtevencoin.ico
convert ${ICON_SRC} -resize 16x16 phtevencoin-16.png
convert ${ICON_SRC} -resize 32x32 phtevencoin-32.png
convert ${ICON_SRC} -resize 48x48 phtevencoin-48.png
convert phtevencoin-16.png phtevencoin-32.png phtevencoin-48.png ${ICON_DST}

