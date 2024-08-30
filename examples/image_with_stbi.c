// clang-format off

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define POTLOT_IMPLEMENTATION
#include "../potlot.h"

int salt_noise_fn(plt_image*im, int row, int col, int px){
  double r = (double)rand()/(double) RAND_MAX;
  if (r < 0.005) return 0x000000;
  if (r < 0.01) return 0xffffff;
  return px;
}


int main(void) {
  int img_width;
  int img_height;
  int img_channels;

  unsigned char *img_stbi = stbi_load(
    "../assets/rabbit.jpg", &img_width, &img_height, &img_channels, 0);

  plt_image *img = plt_from_stbi_uc_rgb(img_stbi, img_width, img_height);
  plt_color_convert(img, PLT_COLOR_GRAY);

  // add salt and pepper noise
  plt_pixel_map(img, salt_noise_fn);
  plt_save_ppm(img, "rabbit_noisy.ppm");

  // median filter
  plt_filter_median(img, 3, 3);
  plt_save_ppm(img, "rabbit_clean.ppm");


  // blur using custom filter
  float filter[] = {
    1/9.f, 1/9.0f, 1/9.0f,
    1/9.f, 1/9.0f, 1/9.0f,
    1/9.f, 1/9.0f, 1/9.0f,
  };
  plt_filter_apply(img, 3, 3, filter);
  plt_filter_apply(img, 3, 3, filter);
  plt_save_ppm(img, "rabbit_clean_blurred.ppm");


  stbi_image_free(img_stbi);
  plt_free(img);
}

