#pragma once

#include <Arduino.h>
#include <esp_display_panel.hpp>

// Waveshare ESP32-S3-Touch-LCD-4.3 / 4.3B
// 800 x 480 RGB panel, ST7262, 16-bit RGB bus.
// Pin mapping follows the Waveshare panel configuration.

#define EXAMPLE_LCD_NAME                        ST7262
#define EXAMPLE_LCD_WIDTH                       (800)
#define EXAMPLE_LCD_HEIGHT                      (480)
#define EXAMPLE_LCD_COLOR_BITS                  (24)
#define EXAMPLE_LCD_RGB_DATA_WIDTH              (16)
#define EXAMPLE_LCD_RGB_COLOR_BITS              (16)

// RGB timing
#define EXAMPLE_LCD_RGB_TIMING_FREQ_HZ          (16 * 1000 * 1000)
#define EXAMPLE_LCD_RGB_TIMING_HPW              (4)
#define EXAMPLE_LCD_RGB_TIMING_HBP              (8)
#define EXAMPLE_LCD_RGB_TIMING_HFP              (8)
#define EXAMPLE_LCD_RGB_TIMING_VPW              (4)
#define EXAMPLE_LCD_RGB_TIMING_VBP              (8)
#define EXAMPLE_LCD_RGB_TIMING_VFP              (8)
#define EXAMPLE_LCD_RGB_BOUNCE_BUFFER_SIZE      (EXAMPLE_LCD_WIDTH * 10)

// RGB pins
#define EXAMPLE_LCD_RGB_IO_DISP                 (-1)
#define EXAMPLE_LCD_RGB_IO_VSYNC                (3)
#define EXAMPLE_LCD_RGB_IO_HSYNC                (46)
#define EXAMPLE_LCD_RGB_IO_DE                   (5)
#define EXAMPLE_LCD_RGB_IO_PCLK                 (7)

#define EXAMPLE_LCD_RGB_IO_DATA0                (1)
#define EXAMPLE_LCD_RGB_IO_DATA1                (2)
#define EXAMPLE_LCD_RGB_IO_DATA2                (42)
#define EXAMPLE_LCD_RGB_IO_DATA3                (41)
#define EXAMPLE_LCD_RGB_IO_DATA4                (40)
#define EXAMPLE_LCD_RGB_IO_DATA5                (39)
#define EXAMPLE_LCD_RGB_IO_DATA6                (0)
#define EXAMPLE_LCD_RGB_IO_DATA7                (45)
#define EXAMPLE_LCD_RGB_IO_DATA8                (48)
#define EXAMPLE_LCD_RGB_IO_DATA9                (47)
#define EXAMPLE_LCD_RGB_IO_DATA10               (21)
#define EXAMPLE_LCD_RGB_IO_DATA11               (14)
#define EXAMPLE_LCD_RGB_IO_DATA12               (38)
#define EXAMPLE_LCD_RGB_IO_DATA13               (18)
#define EXAMPLE_LCD_RGB_IO_DATA14               (17)
#define EXAMPLE_LCD_RGB_IO_DATA15               (10)

// LCD reset/backlight are handled by the board's IO expander.
#define EXAMPLE_LCD_RST_IO                     (-1)
#define EXAMPLE_LCD_BL_IO                      (-1)
#define EXAMPLE_LCD_BL_ON_LEVEL                (1)
#define EXAMPLE_LCD_BL_OFF_LEVEL               (!EXAMPLE_LCD_BL_ON_LEVEL)

// Keep this first test simple. FPS callback is not needed.
#define EXAMPLE_LCD_ENABLE_CREATE_WITH_CONFIG   (0)
#define EXAMPLE_LCD_ENABLE_PRINT_FPS            (0)
#define EXAMPLE_LCD_ENABLE_DRAW_FINISH_CALLBACK (0)

#define _EXAMPLE_LCD_CLASS(name, ...) LCD_##name(__VA_ARGS__)
#define EXAMPLE_LCD_CLASS(name, ...)  _EXAMPLE_LCD_CLASS(name, ##__VA_ARGS__)

void waveshare_lcd_init(void);
void lvgl_init(void);
