#include "readpng.h"

#ifdef TEST // gcc readpng.c -g -Wall -o cx -lpng -DTEST
int main(int argc, char *argv[]) {
  if(argc != 3) {
    fprintf(stderr, "%s [in img name] [out image name]\n", argv[0]);
    exit(1);
  }
  int width, height;
  png_bytep *rowImg = readPngFile(argv[1], &width, &height); // unsigned char ** rowImg

  processPngFile(rowImg, width, height);
  writePngFile(argv[2], rowImg, width, height);
  return 0;
}
#endif

png_bytep * readPngFile(char *filename, int *width, int *height) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) exit(1);

  png_infop info = png_create_info_struct(png);
  if(!info) exit(1);

  if(setjmp(png_jmpbuf(png))) exit(1);

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

void writePngFile(char *filename, png_bytep *row_pointers, int width, int height) {
  FILE *fp = fopen(filename, "wb");
  if(!fp) { fprintf(stderr, "Error writing png file %s", filename); exit(1); }

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) exit(1);

  png_infop info = png_create_info_struct(png);
  if (!info) exit(1);

  if (setjmp(png_jmpbuf(png))) exit(1);

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
}

#ifdef TEST
void processPngFile(png_bytep * row_pointers, int width, int height) {
  for(int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width; x++) {
      // png_bytep px = &(row[x * 4]); // a pixel = [R,G,B,A]
      // printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
      // px[3] = 255/2;
      unsigned char * px = (&(row_pointers[y][x * 4]));
      printf("%i\n", px[3] );
    }
  }
}
#endif
