/**
 * @file max7219_7seg.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief メイン
 * @version 0.1
 * @date 2025-11-12
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "drv_max7219.h"

max7219_reg_config_t g_max7219_config;

void setup()
{
#ifdef DEBUG_SEG_PRINT
    Serial.begin(115200);
#endif

#if 0
    g_max7219_config.reg_decode_mode = DECODE_NONE;
#else
    g_max7219_config.reg_decode_mode = DECODE_CODE_B_FONT;
#endif
    g_max7219_config.reg_brightness = 0x05;
    g_max7219_config.reg_scan_limit = SEG_DIGIT_CNT;
    g_max7219_config.reg_shutdown = 1;
    g_max7219_config.reg_display_test = 0;
    drv_max7219_7seg_init(&g_max7219_config);

#ifdef DEBUG_SEG_TEST
    drv_max7219_7seg_test();
#endif
}

void loop()
{
    drv_max7219_7seg_animation();
}