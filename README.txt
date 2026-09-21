LVGL 9 - Waveshare ESP32-S3-Touch-LCD-4.3
==========================================

This is a CLEAN DISPLAY TEST PROJECT.
It displays the existing Ludwig 800x480 RGB565 background using LVGL 9.
No lap timer or Hall sensor logic is included yet.

FILES
-----
prov_copy_20260919203939.ino
waveshare_lcd_port.h
waveshare_lcd_port.cpp
ludwig_original_empty_exact_colors.h

ARDUINO IDE
-----------
1. Open prov_copy_20260919203939.ino.
2. Select the Waveshare ESP32-S3-Touch-LCD-4.3 board if it exists.
   Otherwise use ESP32S3 Dev Module as recommended by Waveshare for the
   Arduino examples.
3. Flash: 16MB
4. PSRAM: 8MB OPI
5. Compile/upload.

REQUIRED LIBRARIES
------------------
- LVGL 9.x
- ESP32_Display_Panel

IMPORTANT
---------
LVGL must use 16-bit color for this project. The existing lv_conf.h should
contain:

#define LV_COLOR_DEPTH 16

Do not put these project files inside the LVGL library folder. Keep all four
files in the same Arduino sketch folder.

WHAT SHOULD HAPPEN
------------------
After upload/reset, the display should initialize and show the Ludwig
background. Serial Monitor: 115200 baud.

This is deliberately a small baseline. Once this compiles and the background
is correct, the lap timer UI and Hall sensor can be added without mixing LVGL
8 and LVGL 9 APIs.
