This builds on 6_input, and replaces the default SGDK font with something a little nicer.

You need a font image in png format. This needs to have each character 8x8 pixels. There are some here that will require a little editing in GIMP or similar to make work: https://files.somniafabularum.com/fonts/bitmap - use the \sgdk\res\image\font_default.png as a guide.

Create a new .res file, font.res, with the image file referenced:
IMAGE custom_font  "font.png" BEST NONE

Using BEST alone resulted in corruption for me, so I disable "map optimisation" - see "\sgdk\bin\rescomp.txt for more information.

Within int main() issue the commands to load the custom font:
VDP_loadFont(custom_font.tileset, DMA);

In this instance, I want to pull the colours within the font tiles, and set them as PAL0 - pallete 0. This will not work for more complicated projects where specific pallets are to be used, but at this stage it works fine.
VDP_setPalette(PAL0, custom_font.palette->data);
