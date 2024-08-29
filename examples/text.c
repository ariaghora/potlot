// clang-format off

#define POTLOT_IMPLEMENTATION
#include "../potlot.h"

int main(void) {
  int img_width = 300, img_height = 150;

  plt_image *img = plt_init(img_width, img_height);

  plt_text_draw(img, "Hello world, this is...", 10, 10, 0xff00ff);

  const char *large_text = "potlot!";
  int text_width_px = plt_text_measure(large_text, 2);
  plt_text_draw_scaled(img, large_text,
                       img_width/2 - text_width_px/2,
                       img_height/2 - 5,
                       0xffff00, 2);

  plt_save_ppm(img, "text.ppm");
  plt_free(img);
}
