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
    g_max7219_config.reg_decode_mode = DECODE_CODE_B_FONT;
    g_max7219_config.reg_brightness = 0x05;
    g_max7219_config.reg_scan_limit = SEG_DIGIT_CNT;
    g_max7219_config.reg_shutdown = 1;
    g_max7219_config.reg_display_test = 0;
    g_max7219_config.reg_digit_0 = SEG_B_FONT_0;
    g_max7219_config.reg_digit_1 = SEG_B_FONT_1;
    g_max7219_config.reg_digit_2 = SEG_B_FONT_2;
    g_max7219_config.reg_digit_3 = SEG_B_FONT_3;
    g_max7219_config.reg_digit_4 = SEG_B_FONT_4;
    g_max7219_config.reg_digit_5 = SEG_B_FONT_5;
    g_max7219_config.reg_digit_6 = SEG_B_FONT_6;
    g_max7219_config.reg_digit_7 = SEG_B_FONT_7;
    drv_max7219_7seg_init(&g_max7219_config);
}

void loop()
{
    // TODO:
}