// clang-format off

#define POTLOT_IMPLEMENTATION
#include "../potlot.h"

int main(void) {
  int img_width = 300, img_height = 300;

  plt_image *img = plt_init(img_width, img_height);
  plt_rect_fill(img, 0, 0, img_width, img_height, 0xffffff, 0.35);

  plt_rect_draw(img, 20, 20, 280, 280, 0xffffff, 2);
  plt_rect_fill(img, 0, 0, 50, 50, 0xff0000, 1);
  plt_circle_draw(img, 150, 150, 100, 0x00ff00, 3);
  plt_circle_fill(img, 150, 75, 80, 0xffff00, 0.5);
  plt_circle_fill(img, 150, 300-75, 100, 0x00ffff, 0.75);

  plt_save_ppm(img, "shapes.ppm");
  plt_free(img);
}

