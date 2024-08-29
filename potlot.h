// clang-format off
#ifndef _POTLOT_H_
#define _POTLOT_H_

#ifndef PTDEF
#define PTDEF static inline
#endif

#define GLYPH_SIZE     5
#define LETTER_SPACING 2

typedef struct plt_plot {
  int  width, height;
  int *pixels;
} plt_plot;

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

PTDEF plt_plot  *plt_init(int width, int height);
PTDEF void       plt_free(plt_plot *plot);
PTDEF pt_errcode plt_save_ppm(plt_plot *plot, const char *filename);

/*
 * Drawing API
 */
PTDEF void plt_pixel_put(plt_plot *plot, int x, int y, int color, float alpha);
PTDEF void plt_draw_line(plt_plot *plot, int x0, int y0, int x1, int y1, int color, int thickness);
PTDEF void plt_draw_text(plt_plot *plot, const char *text, int x, int y, int color);
PTDEF void plt_draw_text_scaled( plt_plot *plot, const char *text, int x, int y, int color, int scale);

#ifdef  __cplusplus
}
#endif

#ifdef  POTLOT_IMPLEMENTATION
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PLT_MALLOC(s) malloc(s)
#define PLT_FREE(s)   free(s)
#define PLT_RGB(r,g,b) (((r&0xff) << 16) | ((g&0xff) << 8) | (b & 0xff))
#define XORSWAP(a, b) do { a=a^b; b=a^b; a=a^b; } while(0);

PTDEF plt_plot *plt_init(int width, int height) {
  plt_plot *plt = (plt_plot*) PLT_MALLOC(sizeof(*plt));
  plt->pixels   = (int*) PLT_MALLOC(sizeof(int) * width * height);
  plt->width    = width; plt->height=height;
  for (int i = 0; i < width*height; ++i) plt->pixels[i]=0;
  return plt;
}

PTDEF void plt_free(plt_plot *plot) {
  PLT_FREE(plot->pixels);
  PLT_FREE(plot);
}

PTDEF void plt_pixel_put(plt_plot *plot, int x, int y, int color, float alpha) {
  int px   = plot->pixels[y*plot->width + x];
  int r    = (color >> 16) & 0xff;
  int g    = (color >> 8) & 0xff;
  int b    =  color & 0xff;
  int bg_r = (px >> 16) & 0xff;
  int bg_g = (px >> 8) & 0xff;
  int bg_b =  px & 0xff;
  plot->pixels[y*plot->width + x] = PLT_RGB(
    (int)(bg_r * (1-alpha) + r*alpha),
    (int)(bg_g * (1-alpha) + g*alpha),
    (int)(bg_b * (1-alpha) + b*alpha)
  );
}

PTDEF void plt_draw_line(plt_plot *plot, int x0, int y0, int x1, int y1, int color, int width) {
  if (width < 1) width = 1;
  int steep = abs(y1-y0) > abs(x1-x0);
  if (steep) { XORSWAP(x0, y0); XORSWAP(x1, y1); }
  if (x0 > x1) { XORSWAP(x0, x1); XORSWAP(y0, y1); }

  float dx = x1 - x0;
  float dy = y1 - y0;
  float grad = dx > 0 ? dy/dx : 1.0;

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
    plt_pixel_put(plot, ypxl1, xpxl1, color, rfpart*xgap);
    for (int i = 0; i < width; ++i) {
      plt_pixel_put(plot, ypxl1 + i, xpxl1, color, 1);
    }
    plt_pixel_put(plot, ypxl1 + width, xpxl1, color, fpart*xgap);
  } else {
    plt_pixel_put(plot, xpxl1, ypxl1, color, rfpart*xgap);
    for (int i = 0; i < width; ++i) {
      plt_pixel_put(plot, xpxl1 + i, ypxl1, color, 1);
    }
    plt_pixel_put(plot, xpxl1 + width, ypxl1, color, fpart*xgap);
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
    plt_pixel_put(plot, ypxl2, xpxl2, color, rfpart*xgap);
    for (int i = 0; i < width; ++i) {
      plt_pixel_put(plot, ypxl2 + i, xpxl2, color, 1);
    }
    plt_pixel_put(plot, ypxl2 + width, xpxl2, color, fpart*xgap);
  } else {
    plt_pixel_put(plot, xpxl2, ypxl2, color, rfpart*xgap);
    for (int i = 0; i < width; ++i) {
      plt_pixel_put(plot, xpxl2, ypxl2 + i, color, 1);
    }
    plt_pixel_put(plot, xpxl2, ypxl2 + width, color, fpart*xgap);
  }

  if (steep) {
    for (int x=xpxl1+1; x<xpxl2; ++x) {
      fpart = intery - floor(intery);
      rfpart = 1 - fpart;
      float y = floor(intery);

      plt_pixel_put(plot, y, x, color, rfpart);
      for (int i = 1; i < width; ++i) {
        plt_pixel_put(plot, y + i, x, color, 1);
      }
      plt_pixel_put(plot, y + width, x, color, fpart);

      intery = intery + grad;
    }
  } else {
    for (int x=xpxl1+1; x<xpxl2; ++x) {
      fpart = intery - floor(intery);
      rfpart = 1 - fpart;
      float y = floor(intery);

      plt_pixel_put(plot, x, y, color, rfpart);
      for (int i = 1; i < width; ++i) {
        plt_pixel_put(plot, x, y + i, color, 1);
      }
      plt_pixel_put(plot, x, y + width, color, fpart);

      intery = intery + grad;
    }
  }
}

PTDEF void plt_draw_text(plt_plot *plot, const char *text, int x, int y, int color) {
  plt_draw_text_scaled(plot, text, x, y, color, 1);
}

PTDEF void plt_draw_text_scaled(plt_plot *plot, const char *text, int x, int y, int color, int scale) {
  int len = strlen(text);
  for (int cidx=0; cidx<len; ++cidx) {
    for (int crow=0; crow<GLYPH_SIZE*scale; crow+=scale) {
      for (int ccol=0; ccol<GLYPH_SIZE*scale; ccol+=scale) {
        int px_x = ccol+x + cidx*(GLYPH_SIZE*scale + LETTER_SPACING);
        int px_y = crow+y;
        int inside_canvas = (px_y>=0 && px_x>=0 &&
                             px_y<plot->height && px_x<plot->width);
        int has_value = plt_glyphs[text[cidx]][(crow*GLYPH_SIZE)/scale+ccol/scale]==1;

        if (inside_canvas && has_value) {
          for (int rrow=0; rrow<scale; ++rrow)
            for (int rcol=0; rcol<scale; ++rcol)
              plt_pixel_put(plot, px_x+rcol, px_y+rrow, color, 1);
        }
      }
    }
  }
}

PTDEF pt_errcode plt_save_ppm(plt_plot *plot, const char *filename) {
  FILE* fp = fopen(filename, "wb");
  if (!fp) return PT_ERRCODE_IO_ERROR;

  // Write PPM header
  fprintf(fp, "P3\n%d %d\n255\n", plot->width, plot->height);
  // Write pixels to PPM file
  for (int row = 0; row < plot->height; ++row) {
    for (int col = 0; col < plot->width; ++col) {
      int px = plot->pixels[row * plot->width + col];
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
