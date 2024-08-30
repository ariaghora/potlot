// clang-format off
#define POTLOT_IMPLEMENTATION
#include "../potlot.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void) {
  int img_width;
  int img_height;
  int img_channels;

  unsigned char *img_stbi = stbi_load(
    "../assets/rabbit.jpg", &img_width, &img_height, &img_channels, 0);

  plt_image *img = plt_from_stbi_uc_rgb(img_stbi, img_width, img_height);

  plt_rect_fill(img, 230, 10, 400, 200, 0x1155ff, 0.3);
  plt_rect_draw(img, 230, 10, 400, 200, 0x1155ff, 4);
  plt_rect_fill(img, 230, 200, 400, 216, 0x1155ff, 1);
  plt_text_draw_scaled(img, "rabbit, 95%", 234, 204, 0xffffff, 2);

  plt_save_ppm(img, "rabbit_annotated.ppm");
  plt_free(img);
  stbi_image_free(img_stbi);
}

