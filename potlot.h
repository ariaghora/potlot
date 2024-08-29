// clang-format off
#ifndef _POTLOT_H_
#define _POTLOT_H_

#ifndef PTDEF
#define PTDEF static inline
#endif

#define GLYPH_SIZE     5
#define LETTER_SPACING 2

typedef struct plt_image {
  int  width, height;
  int *pixels;
} plt_image;

typedef enum {
  PT_ERRCODE_OK, PT_ERRCODE_IO_ERROR,
} pt_errcode;

/*
 * default pixel font glyphs, each having 5x5 size
 */
static char plt_glyphs[128][GLYPH_SIZE*GLYPH_SIZE] = {
  [' '] = { 0 },
  ['0'] = { 0,1,1,1,0, 1,0,0,1,1, 1,0,1,0,1, 1,1,0,0,1, 0,1,1,1,0 },
  ['1'] = { 0,0,1,0,0, 0,1,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,1,0 },
  ['2'] = { 0,1,1,1,0, 1,0,0,0,1, 0,0,1,1,0, 0,1,0,0,0, 1,1,1,1,1 },
  ['3'] = { 1,1,1,1,1, 0,0,0,1,0, 0,1,1,1,0, 0,0,0,0,1, 1,1,1,1,0 },
  ['4'] = { 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,1, 0,0,0,0,1, 0,0,0,0,1 },
  ['5'] = { 1,1,1,1,0, 1,0,0,0,0, 1,1,1,1,0, 0,0,0,0,1, 1,1,1,1,0 },
  ['6'] = { 0,0,1,1,0, 0,1,0,0,0, 1,1,1,1,0, 1,0,0,0,1, 0,1,1,1,0 },
  ['7'] = { 1,1,1,1,1, 0,0,0,0,1, 0,0,1,1,0, 0,1,0,0,0, 0,1,0,0,0 },
  ['8'] = { 0,1,1,1,0, 1,0,0,0,1, 0,1,1,1,0, 1,0,0,0,1, 0,1,1,1,0 },
  ['9'] = { 0,1,1,1,0, 1,0,0,0,1, 0,1,1,1,1, 0,0,0,0,1, 0,1,1,1,0 },
  ['-'] = { 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0 },
  ['='] = { 0,0,0,0,0, 1,1,1,1,1, 0,0,0,0,0, 1,1,1,1,1, 0,0,0,0,0 },
  ['a'] = { 0,1,1,1,0, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['b'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0 },
  ['c'] = { 0,1,1,1,1, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 0,1,1,1,1 },
  ['d'] = { 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,0 },
  ['e'] = { 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,0, 1,0,0,0,0, 1,1,1,1,1 },
  ['f'] = { 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,0, 1,0,0,0,0, 1,0,0,0,0 },
  ['g'] = { 0,1,1,1,1, 1,0,0,0,0, 1,0,1,1,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['h'] = { 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['i'] = { 0,1,1,1,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,1,0 },
  ['j'] = { 0,0,1,1,1, 0,0,0,0,1, 0,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['k'] = { 1,0,0,0,1, 1,0,0,1,0, 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['l'] = { 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,1 },
  ['m'] = { 1,0,0,0,1, 1,1,0,1,1, 1,0,1,0,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['n'] = { 1,0,0,0,1, 1,1,0,0,1, 1,0,1,0,1, 1,0,0,1,1, 1,0,0,0,1 },
  ['o'] = { 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['p'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,0, 1,0,0,0,0 },
  ['q'] = { 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,1,1, 0,1,1,0,1 },
  ['r'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['s'] = { 0,1,1,1,1, 1,0,0,0,0, 0,1,1,1,1, 0,0,0,0,1, 1,1,1,1,0 },
  ['t'] = { 1,1,1,1,1, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 },
  ['u'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['v'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,0,1,0, 0,0,1,0,0 },
  ['w'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,1,0,1, 1,0,1,0,1, 0,1,0,1,0 },
  ['x'] = { 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['y'] = { 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0, 0,0,1,0,0, 0,0,1,0,0 },
  ['z'] = { 1,1,1,1,1, 0,0,0,1,0, 0,0,1,1,0, 0,1,0,0,0, 1,1,1,1,1 },
  ['!'] = { 0,0,1,1,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,1,0,0 },
  ['@'] = { 0,1,1,1,1, 1,0,1,0,1, 1,0,1,1,1, 1,0,0,0,0, 0,1,1,1,0 },
  ['#'] = { 0,1,0,1,0, 1,1,1,1,1, 0,1,0,1,0, 1,1,1,1,1, 0,1,0,1,0 },
  ['$'] = { 0,0,1,0,0, 0,1,1,1,1, 0,0,1,0,0, 1,1,1,1,0, 0,0,1,0,0 },
  ['%'] = { 1,1,0,0,1, 1,1,0,1,0, 0,0,1,0,0, 0,1,0,1,1, 1,0,0,1,1 },
  ['^'] = { 0,1,1,1,0, 1,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 },
  ['&'] = { 0,1,1,0,0, 1,0,0,0,0, 0,1,1,0,1, 1,0,0,1,0, 0,1,1,0,1 },
  ['*'] = { 1,0,1,0,1, 0,1,1,1,0, 1,1,1,1,1, 0,1,1,1,0, 1,0,1,0,1 },
  ['('] = { 0,0,1,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,0,1,0,0 },
  [')'] = { 0,0,1,0,0, 0,0,0,1,0, 0,0,0,1,0, 0,0,0,1,0, 0,0,1,0,0 },
  ['_'] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1 },
  ['+'] = { 0,0,1,0,0, 0,0,1,0,0, 1,1,1,1,1, 0,0,1,0,0, 0,0,1,0,0 },
  [','] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0 },
  ['.'] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0 },
  ['?'] = { 0,1,1,1,0, 1,0,0,0,1, 0,0,1,1,0, 0,0,0,0,0, 0,0,1,0,0 },
};


#ifdef  __cplusplus
extern "C" {
#endif

PTDEF plt_image  *plt_init(int width, int height);
PTDEF void        plt_free(plt_image *im);
PTDEF pt_errcode  plt_save_ppm(plt_image *im, const char *filename);

/*
 * Drawing API
 */
PTDEF void plt_pixel_put(plt_image *im, int x, int y, int color, float alpha);
PTDEF void plt_draw_line(plt_image *im, int x0, int y0, int x1, int y1, int color, int thickness);
PTDEF void plt_text_draw(plt_image *im, const char *text, int x, int y, int color);
PTDEF void plt_text_draw_scaled(plt_image *im, const char *text, int x, int y, int color, int scale);
PTDEF int  plt_text_measure(const char *text, int scale);

#ifdef  __cplusplus
}
#endif

#ifdef  POTLOT_IMPLEMENTATION
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PLT_MALLOC(s) malloc(s)
#define PLT_FREE(s)   free(s)

#define plt__xorswap(a, b) do { a=a^b; b=a^b; a=a^b; } while(0);
#define plt__rgb(r,g,b)    (((r&0xff) << 16) | ((g&0xff) << 8) | (b & 0xff))
#define plt__r_i32(px)     ((px >> 16) & 0xff)
#define plt__g_i32(px)     ((px >> 8) & 0xff)
#define plt__b_i32(px)     (px & 0xff)
#define plt__r_f32(px)     (plt__r_i32(px) / 255f)
#define plt__g_f32(px)     (plt__g_i32(px) / 255f)
#define plt__b_f32(px)     (plt__b_i32(px) / 255f)

PTDEF plt_image *plt_init(int width, int height) {
  plt_image *plt = (plt_image*) PLT_MALLOC(sizeof(*plt));
  plt->pixels   = (int*) PLT_MALLOC(sizeof(int) * width * height);
  plt->width    = width; plt->height=height;
  for (int i = 0; i < width*height; ++i) plt->pixels[i]=0;
  return plt;
}

PTDEF void plt_free(plt_image *im) {
  PLT_FREE(im->pixels);
  PLT_FREE(im);
}

PTDEF void plt_pixel_put(plt_image *im, int x, int y, int color, float alpha) {
  /* This will put pixel on buffer with alpha blending strategy. */
  int r    = plt__r_i32(color);
  int g    = plt__g_i32(color);
  int b    = plt__b_i32(color);
  int px   = im->pixels[y*im->width + x];
  int bg_r = plt__r_i32(px);
  int bg_g = plt__g_i32(px);
  int bg_b = plt__b_i32(px);
  im->pixels[y*im->width + x] = plt__rgb(
    (int)(bg_r * (1-alpha) + r*alpha),
    (int)(bg_g * (1-alpha) + g*alpha),
    (int)(bg_b * (1-alpha) + b*alpha)
  );
}

PTDEF void plt_draw_line(plt_image *im, int x0, int y0, int x1, int y1, int color, int width) {
  if (width < 1) width = 1;
  int steep = abs(y1-y0) > abs(x1-x0);

  if (steep)   { plt__xorswap(x0, y0); plt__xorswap(x1, y1); }
  if (x0 > x1) { plt__xorswap(x0, x1); plt__xorswap(y0, y1); }

  float dx   = x1 - x0;
  float dy   = y1 - y0;
  float grad = dx > 0 ? (dy/dx) : 1.0;

  // rotate w
  width = width * sqrt(1 + grad*grad);

  // First endpoint
  float x_end  = round(x0);
  float y_end  = y0 - (width - 1) * 0.5 + grad * (x_end - x0);
  float xgap   = 1 - (x0 + 0.5 - x_end);
  float xpxl1  = x_end;
  float ypxl1  = floor(y_end);
  float fpart  = y_end - floor(y_end);
  float rfpart = 1 - fpart;

  if (steep) {
    plt_pixel_put(im, ypxl1, xpxl1, color, rfpart*xgap);
    for (int i = 1; i < width; ++i) 
      plt_pixel_put(im, ypxl1 + i, xpxl1, color, 1);
    plt_pixel_put(im, ypxl1 + width, xpxl1, color, fpart*xgap);
  } else {
    plt_pixel_put(im, xpxl1, ypxl1, color, rfpart*xgap);
    for (int i = 1; i < width; ++i) 
      plt_pixel_put(im, xpxl1, ypxl1 + i, color, 1);
    plt_pixel_put(im, xpxl1, ypxl1 + width, color, fpart*xgap);
  }

  float intery = y_end + grad;

  x_end = round(x1);
  y_end = y1 - (width - 1) * 0.5 + grad * (x_end - x1);
  xgap = 1 - (x1 + 0.5 - x_end);
  float xpxl2 = x_end;
  float ypxl2 = floor(y_end);
  fpart = y_end - floor(y_end);
  rfpart = 1 - fpart;

  if (steep) {
    plt_pixel_put(im, ypxl2, xpxl2, color, rfpart*xgap);
    for (int i = 1; i < width; ++i) 
      plt_pixel_put(im, ypxl2 + i, xpxl2, color, 1);
    plt_pixel_put(im, ypxl2 + width, xpxl2, color, fpart*xgap);
  } else {
    plt_pixel_put(im, xpxl2, ypxl2, color, rfpart*xgap);
    for (int i = 1; i < width; ++i) 
      plt_pixel_put(im, xpxl2, ypxl2 + i, color, 1);
    plt_pixel_put(im, xpxl2, ypxl2 + width, color, fpart*xgap);
  }

  if (steep) {
    for (int x=xpxl1+1; x<xpxl2; ++x) {
      fpart = intery - floor(intery);
      rfpart = 1 - fpart;
      float y = floor(intery);

      plt_pixel_put(im, y, x, color, rfpart);
      for (int i = 1; i < width; ++i)
        plt_pixel_put(im, y + i, x, color, 1);
      plt_pixel_put(im, y + width, x, color, fpart);

      intery = intery + grad;
    }
  } else {
    for (int x=xpxl1+1; x<xpxl2; ++x) {
      fpart = intery - floor(intery);
      rfpart = 1 - fpart;
      float y = floor(intery);

      plt_pixel_put(im, x, y, color, rfpart);
      for (int i = 1; i < width; ++i)
        plt_pixel_put(im, x, y + i, color, 1);
      plt_pixel_put(im, x, y + width, color, fpart);

      intery = intery + grad;
    }
  }
}

PTDEF void plt_text_draw(plt_image *im, const char *text, int x, int y, int color) {
  plt_text_draw_scaled(im, text, x, y, color, 1);
}

PTDEF void plt_text_draw_scaled(plt_image *im, const char *text, int x, int y, int color, int scale) {
  int len        = strlen(text);
  for (int cidx=0; cidx<len; ++cidx) {
    for (int c_row=0; c_row<GLYPH_SIZE*scale; c_row+=scale) {
      for (int c_col=0; c_col<GLYPH_SIZE*scale; c_col+=scale) {
        int px_x = c_col+x + cidx*(GLYPH_SIZE*scale + LETTER_SPACING);
        int px_y = c_row+y;

        int inside_canvas = (px_y>=0 && px_x>=0 &&
                             px_y<im->height && px_x<im->width);
        int has_value     = plt_glyphs[text[cidx]][(c_row*GLYPH_SIZE)/scale + (c_col/scale)]==1;

        if (inside_canvas && has_value) {
          for (int rep_row=0; rep_row<scale; ++rep_row)
            for (int rep_col=0; rep_col<scale; ++rep_col)
              plt_pixel_put(im, px_x+rep_col, px_y+rep_row, color, 1);
        }
      }
    }
  }
}

PTDEF int plt_text_measure(const char *text, int scale){
  if (strlen(text) == 0) return 0;
  return (GLYPH_SIZE*scale + LETTER_SPACING)*(strlen(text)) - LETTER_SPACING;
}

PTDEF pt_errcode plt_save_ppm(plt_image *im, const char *filename) {
  FILE* fp = fopen(filename, "wb");
  if (!fp) return PT_ERRCODE_IO_ERROR;

  // Write PPM header
  fprintf(fp, "P3\n%d %d\n255\n", im->width, im->height);
  // Write pixels to PPM file
  for (int row = 0; row < im->height; ++row) {
    for (int col = 0; col < im->width; ++col) {
      int px = im->pixels[row * im->width + col];
      int r = (px >> 16) & 0xff;
      int g = (px >> 8) & 0xff;
      int b = px & 0xff;
      fprintf(fp, "%d %d %d ", r, g, b);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
  return PT_ERRCODE_OK;
}

#endif // PLOT_IMPLEMENTATION

#endif //!_PLOT_H_