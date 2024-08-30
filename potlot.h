// clang-format off
#ifndef _POTLOT_H_
#define _POTLOT_H_

#ifndef PTDEF
#define PTDEF static inline
#endif

#define GLYPH_SIZE     5
#define LETTER_SPACING 2

typedef enum {
  PLT_COLOR_RGB, PLT_COLOR_GRAY
} plt_color_format;

typedef struct plt_image {
  int              width, height;
  int             *pixels;
  plt_color_format  color_format;
} plt_image;

typedef enum {
  PLT_ERRCODE_OK, PLT_ERRCODE_IO_ERROR,
} plt_errcode;

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
  ['A'] = { 0,1,1,1,0, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['B'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0 },
  ['C'] = { 0,1,1,1,1, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 0,1,1,1,1 },
  ['D'] = { 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,0 },
  ['E'] = { 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,0, 1,0,0,0,0, 1,1,1,1,1 },
  ['F'] = { 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,0, 1,0,0,0,0, 1,0,0,0,0 },
  ['G'] = { 0,1,1,1,1, 1,0,0,0,0, 1,0,1,1,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['H'] = { 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['I'] = { 0,1,1,1,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,1,0 },
  ['J'] = { 0,0,1,1,1, 0,0,0,0,1, 0,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['K'] = { 1,0,0,0,1, 1,0,0,1,0, 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['L'] = { 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,1 },
  ['M'] = { 1,0,0,0,1, 1,1,0,1,1, 1,0,1,0,1, 1,0,0,0,1, 1,0,0,0,1 },
  ['N'] = { 1,0,0,0,1, 1,1,0,0,1, 1,0,1,0,1, 1,0,0,1,1, 1,0,0,0,1 },
  ['O'] = { 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['P'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,0, 1,0,0,0,0 },
  ['Q'] = { 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,1,1, 0,1,1,0,1 },
  ['R'] = { 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['S'] = { 0,1,1,1,1, 1,0,0,0,0, 0,1,1,1,1, 0,0,0,0,1, 1,1,1,1,0 },
  ['T'] = { 1,1,1,1,1, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 },
  ['U'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0 },
  ['V'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,0,1,0, 0,0,1,0,0 },
  ['W'] = { 1,0,0,0,1, 1,0,0,0,1, 1,0,1,0,1, 1,0,1,0,1, 0,1,0,1,0 },
  ['X'] = { 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1 },
  ['Y'] = { 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0, 0,0,1,0,0, 0,0,1,0,0 },
  ['Z'] = { 1,1,1,1,1, 0,0,0,1,0, 0,0,1,1,0, 0,1,0,0,0, 1,1,1,1,1 },
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

PTDEF plt_image   *plt_init(int width, int height);
PTDEF plt_image   *plt_from_stbi_uc_rgb(unsigned char *data, int width, int height);
PTDEF void         plt_free(plt_image *im);
PTDEF plt_errcode  plt_save_ppm(plt_image *im, const char *filename);

PTDEF void plt_color_convert(plt_image *im, plt_color_format target_fmt);
PTDEF void plt_filter_median(plt_image *im, int f_w, int f_h);
PTDEF void plt_filter_apply(plt_image *im, int f_w, int f_h, float *f_data);
PTDEF void plt_window_apply_fn(plt_image *im, int win_w, int win_h, int (*map_fn)(plt_image*, int*, int, int));
PTDEF void plt_line_draw(plt_image *im, int x0, int y0, int x1, int y1, int color, int thickness);
PTDEF void plt_pixel_map(plt_image *im, int (*map_fn)(plt_image*im, int row, int col, int px));
PTDEF void plt_pixel_put(plt_image *im, int x, int y, int color, float alpha);
PTDEF void plt_text_draw(plt_image *im, const char *text, int x, int y, int color);
PTDEF void plt_text_draw_scaled(plt_image *im, const char *text, int x, int y, int color, int scale);
PTDEF int  plt_text_measure(const char *text, int scale);

#ifdef  __cplusplus
}
#endif

#ifdef  POTLOT_IMPLEMENTATION
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PLT_MALLOC(s) malloc(s)
#define PLT_FREE(s)   free(s)

#define plt__xorswap(a, b) do { a=a^b; b=a^b; a=a^b; } while(0);
#define mt__clampf(v)      (fmin(1, fmax(v, 0)))
#define plt__rgb(r,g,b)    (((r&0xff) << 16) | ((g&0xff) << 8) | (b & 0xff))
#define plt__r_i32(px)     ((px >> 16) & 0xff)
#define plt__g_i32(px)     ((px >> 8) & 0xff)
#define plt__b_i32(px)     (px & 0xff)
#define plt__r_f32(px)     (plt__r_i32(px) / 255.0f)
#define plt__g_f32(px)     (plt__g_i32(px) / 255.0f)
#define plt__b_f32(px)     (plt__b_i32(px) / 255.0f)

#define plt__panic(msg) do {                             \
    printf("error:%s:%s: %sn", __FILE__, __LINE__, msg); \
    exit(1);                                             \
} while(0);


PTDEF plt_image *plt_init(int width, int height) {
  plt_image *plt = (plt_image*) PLT_MALLOC(sizeof(*plt));
  plt->pixels   = (int*) PLT_MALLOC(sizeof(int) * width * height);
  plt->width    = width; plt->height=height;
  plt->color_format = PLT_COLOR_RGB;
  for (int i = 0; i < width*height; ++i) plt->pixels[i]=0;
  return plt;
}

PTDEF plt_image  *plt_from_stbi_uc_rgb(unsigned char *data, int width, int height) {
  size_t px_count = width * height * 3;
  plt_image *plt = (plt_image*) PLT_MALLOC(sizeof(*plt));
  plt->pixels   = (int*) PLT_MALLOC(sizeof(int) * px_count);
  plt->width    = width; plt->height=height;
  plt->color_format = PLT_COLOR_RGB;
  // convert stb_image data into packed rgb
  for (int i=0; i < px_count; ++i) 
    plt->pixels[i] = plt__rgb(data[i*3], data[i*3+1], data[i*3+2]);
  
  return plt;
}

PTDEF void plt_free(plt_image *im) {
  PLT_FREE(im->pixels);
  PLT_FREE(im);
}

PTDEF void plt_pixel_map(plt_image *im, int (*map_fn)(plt_image*im, int row, int col, int px)) {
  for (int row=0; row<im->height; ++row) {
    for (int col=0; col<im->width; ++col) {
      int px = im->pixels[row*im->width + col];
      int res = map_fn(im, row, col, px);
      im->pixels[row*im->width + col] = res;
    }
  }
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

PTDEF void plt_color_convert(plt_image *im, plt_color_format target_fmt) {
  if (im->color_format == target_fmt) return;

  // NTSC formula: https://en.wikipedia.org/wiki/Grayscale
  if (target_fmt == PLT_COLOR_GRAY) {
    for (int i = 0; i < im->width * im->height; ++i) {
      float r = plt__r_f32(im->pixels[i]);
      float g = plt__g_f32(im->pixels[i]);
      float b = plt__b_f32(im->pixels[i]);
      float gr = (0.299*r + 0.587*g + 0.114*b);
      gr = fmin(1, fmax(gr, 0));
      im->pixels[i] = plt__rgb((int)(gr*255), (int)(gr*255), (int)(gr*255));
    } 
    im->color_format = PLT_COLOR_GRAY;
  }
}

PTDEF int plt__cmp(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}

PTDEF int plt__median(plt_image *im, int *pixel, int win_w, int win_h) {
  if (im->color_format != PLT_COLOR_GRAY) {
    plt__panic("Color must be PLT_COLOR_GRAY");
  }

  int px_count = win_w * win_h;
  int r_values[px_count];
  int g_values[px_count];
  int b_values[px_count];
  for (int i=0; i<px_count; ++i) {
    r_values[i] = plt__r_i32(pixel[i]);
    g_values[i] = plt__g_i32(pixel[i]);
    b_values[i] = plt__b_i32(pixel[i]);
  }
  // Sort the arrays
  qsort(r_values, px_count, sizeof(int), plt__cmp);
  qsort(g_values, px_count, sizeof(int), plt__cmp);
  qsort(b_values, px_count, sizeof(int), plt__cmp);

  // Get the median values
  int med_r = r_values[px_count / 2];
  int med_g = g_values[px_count / 2];
  int med_b = b_values[px_count / 2];
  return plt__rgb(med_r, med_g, med_b);
}

PTDEF void plt_filter_median(plt_image *im, int f_w, int f_h) {
  return plt_window_apply_fn(im, f_w, f_h, plt__median);
}

PTDEF void plt_filter_apply(plt_image *im, int f_w, int f_h, float *f_data) {
  for (int row=0; row<im->height; ++row) {
    for (int col=0; col<im->width; ++col) {
      float r_sum = 0, g_sum = 0, b_sum = 0;
      for (int f_row = 0; f_row < f_h; ++f_row) {
        int px_row = row + f_row - f_h/2;
        if (px_row < 0 || px_row >= im->height) continue;
        for (int f_col = 0; f_col < f_w; ++f_col) {
          int px_col = col + f_col - f_w/2;
          if (px_col < 0 || px_col >= im->width) continue;

          float f_val = f_data[f_row*f_w + f_col];
          int px = im->pixels[px_row*im->width + px_col];
          r_sum = r_sum + plt__r_f32(px) * f_val;
          g_sum = g_sum + plt__g_f32(px) * f_val;
          b_sum = b_sum + plt__b_f32(px) * f_val;
        }
      }

      im->pixels[row*im->width+col] = plt__rgb(
        (int)(mt__clampf(r_sum)*255),
        (int)(mt__clampf(g_sum)*255),
        (int)(mt__clampf(b_sum)*255)
      );
    }
  }
}

PTDEF void plt_window_apply_fn(plt_image *im, int win_w, int win_h, int (*map_fn)(plt_image*, int*, int, int)) {
  for (int row=0; row<im->height; ++row) {
    for (int col=0; col<im->width; ++col) {
      int im_window[win_w*win_h];
      for (int f_row = 0; f_row < win_h; ++f_row) {
        int px_row = row + f_row - win_h/2;
        for (int f_col = 0; f_col < win_w; ++f_col) {
          int px_col = col + f_col - win_w/2;
          if (px_row < 0 || px_row >= im->height || px_col < 0 || px_col >= im->width) {
            im_window[f_row*win_w + f_col] = -1;
          } else {
            int px = im->pixels[px_row*im->width + px_col];
            im_window[f_row*win_w + f_col] = px;
          }
        }
      }
      im->pixels[row*im->width+col] = map_fn(im, im_window, win_w, win_h);
    }
  }
}

PTDEF void plt_line_draw(plt_image *im, int x0, int y0, int x1, int y1, int color, int width) {
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
        int has_value     = plt_glyphs[toupper(text[cidx])][(c_row*GLYPH_SIZE)/scale + (c_col/scale)]==1;

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

PTDEF plt_errcode plt_save_ppm(plt_image *im, const char *filename) {
  FILE* fp = fopen(filename, "wb");
  if (!fp) return PLT_ERRCODE_IO_ERROR;

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
  return PLT_ERRCODE_OK;
}

#endif // PLOT_IMPLEMENTATION

#endif //!_PLOT_H_
