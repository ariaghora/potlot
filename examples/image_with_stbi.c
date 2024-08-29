// clang-format off

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define POTLOT_IMPLEMENTATION
#include "../potlot.h"

int main(void) {
  int img_width;
  int img_height;
  int img_channels;

  unsigned char *img_stbi = stbi_load(
    "../assets/rabbit.jpg", &img_width, &img_height, &img_channels, 0);

  plt_image *img = plt_from_stbi_uc_rgb(img_stbi, img_width, img_height);

  // blur
  float filter[] = {
    1/9.f, 1/9.0f, 1/9.0f,
    1/9.f, 1/9.0f, 1/9.0f,
    1/9.f, 1/9.0f, 1/9.0f,
  };
  plt_filter_apply(img, 3, 3, filter);

  plt_color_convert(img, PLT_COLOR_GRAY);
  plt_save_ppm(img, "rabbit.ppm");

  stbi_image_free(img_stbi);
  plt_free(img);
}

