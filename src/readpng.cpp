#include "include/readpng.h"

png_bytep * readPngFile(const char *filename, int *width, int *height) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) return NULL;

  png_infop info = png_create_info_struct(png);
  if(!info) return NULL;

  if(setjmp(png_jmpbuf(png))) return NULL;

  png_init_io(png, fp);
  png_read_info(png, info);

  int w = png_get_image_width(png, info);
  int h = png_get_image_height(png, info);

  png_byte color_type = png_get_color_type(png, info);
  png_byte bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * h);
  for(int y = 0; y < h; y++)
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));

  png_read_image(png, row_pointers);
  fclose(fp);

  *width = w;
  *height = h;
  return row_pointers;
}

int writePngFile(const char *filename, png_bytep *row_pointers, int width, int height) {
  FILE *fp = fopen(filename, "wb");
  if(!fp) return 1;

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) return 1;

  png_infop info = png_create_info_struct(png);
  if (!info) return 1;

  if (setjmp(png_jmpbuf(png))) return 1;

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
    png,
    info,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  png_set_filler(png, 0, PNG_FILLER_AFTER); // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);

  fclose(fp);
  return 0;
}

int samePx(png_bytep px1, png_bytep px2) {
  if (px1[0] == px2[0] && // R
      px1[1] == px2[1] && // G
      px1[2] == px2[2] && // B
      px1[3] == px2[3])   // A
    return 1;
  return 0;
}

png_bytep * neiPx(png_bytep * img, int x, int y, int w, int h, int * n) {
  *n = 0;
  png_bytep * nei = (png_bytep *) malloc(8 * sizeof(png_bytep));
  if (nei == NULL) { fprintf(stderr, "error malloc in neiPx\n"); exit(1); }

  for(int yi = y-1; (yi <= y+1) && (yi < h); yi++) {
    if (yi < 0) continue;
    png_bytep row = img[yi];
    for(int xi = x-1; (xi <= x+1) && (xi < w); xi++) {
      if (xi < 0 || (xi == x && yi == y)) continue;
      nei[(*n)++] = &(row[xi * 4]);
    }
  }
  return nei;
}
