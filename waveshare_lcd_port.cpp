
#include "waveshare_lcd_port.h"
#include "ludwig_original_empty_exact_colors.h"

#include <lvgl.h>

using namespace esp_panel::drivers;

LCD *lcd = nullptr;

// --------------------------------------------------
// LVGL
// --------------------------------------------------

static uint32_t lvgl_tick()
{
    return millis();
}

static void lvgl_flush(
    lv_display_t *display,
    const lv_area_t *area,
    uint8_t *px_map)
{
    uint32_t width = lv_area_get_width(area);
    uint32_t height = lv_area_get_height(area);

    if (lcd != nullptr)
    {
        lcd->drawBitmap(
            area->x1,
            area->y1,
            width,
            height,
            px_map
        );
    }

    lv_display_flush_ready(display);
}

// --------------------------------------------------
// LCD creation
// --------------------------------------------------

static LCD *create_lcd_without_config(void)
{
    BusRGB *bus = new BusRGB(
#if EXAMPLE_LCD_RGB_DATA_WIDTH == 8

        EXAMPLE_LCD_RGB_IO_DATA0,
        EXAMPLE_LCD_RGB_IO_DATA1,
        EXAMPLE_LCD_RGB_IO_DATA2,
        EXAMPLE_LCD_RGB_IO_DATA3,
        EXAMPLE_LCD_RGB_IO_DATA4,
        EXAMPLE_LCD_RGB_IO_DATA5,
        EXAMPLE_LCD_RGB_IO_DATA6,
        EXAMPLE_LCD_RGB_IO_DATA7,

        EXAMPLE_LCD_RGB_IO_HSYNC,
        EXAMPLE_LCD_RGB_IO_VSYNC,
        EXAMPLE_LCD_RGB_IO_PCLK,
        EXAMPLE_LCD_RGB_IO_DE,
        EXAMPLE_LCD_RGB_IO_DISP,

        EXAMPLE_LCD_RGB_TIMING_FREQ_HZ,
        EXAMPLE_LCD_WIDTH,
        EXAMPLE_LCD_HEIGHT,

        EXAMPLE_LCD_RGB_TIMING_HPW,
        EXAMPLE_LCD_RGB_TIMING_HBP,
        EXAMPLE_LCD_RGB_TIMING_HFP,

        EXAMPLE_LCD_RGB_TIMING_VPW,
        EXAMPLE_LCD_RGB_TIMING_VBP,
        EXAMPLE_LCD_RGB_TIMING_VFP

#elif EXAMPLE_LCD_RGB_DATA_WIDTH == 16

        EXAMPLE_LCD_RGB_IO_DATA0,
        EXAMPLE_LCD_RGB_IO_DATA1,
        EXAMPLE_LCD_RGB_IO_DATA2,
        EXAMPLE_LCD_RGB_IO_DATA3,
        EXAMPLE_LCD_RGB_IO_DATA4,
        EXAMPLE_LCD_RGB_IO_DATA5,
        EXAMPLE_LCD_RGB_IO_DATA6,
        EXAMPLE_LCD_RGB_IO_DATA7,
        EXAMPLE_LCD_RGB_IO_DATA8,
        EXAMPLE_LCD_RGB_IO_DATA9,
        EXAMPLE_LCD_RGB_IO_DATA10,
        EXAMPLE_LCD_RGB_IO_DATA11,
        EXAMPLE_LCD_RGB_IO_DATA12,
        EXAMPLE_LCD_RGB_IO_DATA13,
        EXAMPLE_LCD_RGB_IO_DATA14,
        EXAMPLE_LCD_RGB_IO_DATA15,

        EXAMPLE_LCD_RGB_IO_HSYNC,
        EXAMPLE_LCD_RGB_IO_VSYNC,
        EXAMPLE_LCD_RGB_IO_PCLK,
        EXAMPLE_LCD_RGB_IO_DE,
        EXAMPLE_LCD_RGB_IO_DISP,

        EXAMPLE_LCD_RGB_TIMING_FREQ_HZ,
        EXAMPLE_LCD_WIDTH,
        EXAMPLE_LCD_HEIGHT,

        EXAMPLE_LCD_RGB_TIMING_HPW,
        EXAMPLE_LCD_RGB_TIMING_HBP,
        EXAMPLE_LCD_RGB_TIMING_HFP,

        EXAMPLE_LCD_RGB_TIMING_VPW,
        EXAMPLE_LCD_RGB_TIMING_VBP,
        EXAMPLE_LCD_RGB_TIMING_VFP

#endif
    );

    return new EXAMPLE_LCD_CLASS(
        EXAMPLE_LCD_NAME,
        bus,
        EXAMPLE_LCD_WIDTH,
        EXAMPLE_LCD_HEIGHT,
        EXAMPLE_LCD_COLOR_BITS,
        EXAMPLE_LCD_RST_IO
    );
}

// --------------------------------------------------
// LCD initialization
// --------------------------------------------------

void waveshare_lcd_init(void)
{
#if EXAMPLE_LCD_ENABLE_CREATE_WITH_CONFIG

    Serial.println("Initializing RGB LCD with config");
    lcd = create_lcd_with_config();

#else

    Serial.println("Initializing RGB LCD without config");
    lcd = create_lcd_without_config();

#endif

    auto bus = static_cast<BusRGB *>(lcd->getBus());

    bus->configRGB_BounceBufferSize(
        EXAMPLE_LCD_RGB_BOUNCE_BUFFER_SIZE
    );

    lcd->init();

#if EXAMPLE_LCD_ENABLE_PRINT_FPS

    lcd->attachRefreshFinishCallback(
        onLCD_RefreshFinishCallback
    );

#endif

    lcd->reset();

    assert(lcd->begin());

    if (lcd->getBasicAttributes()
            .basic_bus_spec
            .isFunctionValid(
                LCD::BasicBusSpecification::FUNC_DISPLAY_ON_OFF
            ))
    {
        lcd->setDisplayOnOff(true);
    }

    


}

// --------------------------------------------------
// LVGL initialization
// --------------------------------------------------

void lvgl_init(void)
{
    lv_init();

    lv_tick_set_cb(lvgl_tick);

    static uint8_t draw_buffer[
        EXAMPLE_LCD_WIDTH *
        40 *
        (LV_COLOR_DEPTH / 8)
    ];

    lv_display_t *display = lv_display_create(
        EXAMPLE_LCD_WIDTH,
        EXAMPLE_LCD_HEIGHT
    );

    lv_display_set_flush_cb(
        display,
        lvgl_flush
    );

    lv_display_set_buffers(
        display,
        draw_buffer,
        nullptr,
        sizeof(draw_buffer),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );

    Serial.println("LVGL initialized");
}