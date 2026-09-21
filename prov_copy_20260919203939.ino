#include "waveshare_lcd_port.h"
#include "ludwig_original_empty_exact_colors.h"
#include <lvgl.h>

// Ludwig background: 800 x 480 RGB565.
static const lv_image_dsc_t ludwig_image = {
    .header = {
        .cf = LV_COLOR_FORMAT_RGB565,
        .w = 800,
        .h = 480,
        .stride = 800 * 2
    },
    .data_size = 800 * 480 * 2,
    .data = reinterpret_cast<const uint8_t *>(ludwig_image_rgb565)
};

void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("LVGL 9 + Waveshare 4.3 test");

    waveshare_lcd_init();
    lvgl_init();

    lv_obj_t *screen = lv_screen_active();

    lv_obj_t *image = lv_image_create(screen);
    lv_image_set_src(image, &ludwig_image);
    lv_obj_set_pos(image, 0, 0);

    Serial.println("Background loaded");
}

void loop()
{
    lv_timer_handler();
    delay(5);
}
