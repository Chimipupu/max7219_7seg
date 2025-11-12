/**
 * @file drv_max7219.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief MAX7219ドライバ (for Arduino IDE)
 * @version 0.1
 * @date 2025-11-12
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */
#include "drv_max7219.h"

max7219_reg_config_t *gp_config;

void drv_max7219_config_reg(uint8_t addr, uint8_t val)
{
    digitalWrite(SS, LOW);
    SPI.transfer(addr);
    SPI.transfer(val);
    digitalWrite(SS, HIGH);
}

void drv_max7219_display_7seg(uint32_t val)
{
    uint8_t d = 0;
    uint8_t i = 0;
    uint32_t v = 0;
    uint8_t idx = 0;
    uint8_t digits[8];

    if(gp_config->reg_decode_mode != DECODE_CODE_B_FONT) {
        drv_max7219_config_reg(REG_DECODE_MODE,  DECODE_CODE_B_FONT);
    }

    for (i = 0; i < 8; i++)
    {
        digits[i] = SEG_B_FONT_BLANK;
    }

    if (val == 0) {
        digits[0] = SEG_B_FONT_0;
    } else {
        v = val;
        idx = 0;
        while (v > 0 && idx < 8) {
            d = v % 10;
            digits[idx++] = (uint8_t)(SEG_B_FONT_0 + d);
            v /= 10;
        }
    }

    for (i = 0; i < 8; i++)
    {
        drv_max7219_config_reg(REG_DIGIT_0 + i, digits[i]);
    }
}

void drv_max7219_7seg_init(max7219_reg_config_t *p_config)
{
    gp_config = p_config;

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    drv_max7219_config_reg(REG_BRIGHTNESS,   p_config->reg_brightness);
    drv_max7219_config_reg(REG_SCAN_LIMIT,   p_config->reg_scan_limit);
    drv_max7219_config_reg(REG_SHUTDOWN,     p_config->reg_shutdown);
    drv_max7219_config_reg(REG_DISPLAY_TEST, p_config->reg_display_test);
    drv_max7219_config_reg(REG_DECODE_MODE,  p_config->reg_decode_mode);

#if 1
    if(p_config->reg_decode_mode == DECODE_CODE_B_FONT) {
        // 「01234567」を表示
        drv_max7219_config_reg(REG_DIGIT_7, SEG_B_FONT_0);
        drv_max7219_config_reg(REG_DIGIT_6, SEG_B_FONT_1);
        drv_max7219_config_reg(REG_DIGIT_5, SEG_B_FONT_2);
        drv_max7219_config_reg(REG_DIGIT_4, SEG_B_FONT_3);
        drv_max7219_config_reg(REG_DIGIT_3, SEG_B_FONT_4);
        drv_max7219_config_reg(REG_DIGIT_2, SEG_B_FONT_5);
        drv_max7219_config_reg(REG_DIGIT_1, SEG_B_FONT_6);
        drv_max7219_config_reg(REG_DIGIT_0, SEG_B_FONT_7);
    } else {
        // 「AbCdEF-.」を表示
        drv_max7219_config_reg(REG_DIGIT_7, SEG_CHAR_A);
        drv_max7219_config_reg(REG_DIGIT_6, SEG_CHAR_B);
        drv_max7219_config_reg(REG_DIGIT_5, SEG_CHAR_C);
        drv_max7219_config_reg(REG_DIGIT_4, SEG_CHAR_D);
        drv_max7219_config_reg(REG_DIGIT_3, SEG_CHAR_E);
        drv_max7219_config_reg(REG_DIGIT_2, SEG_CHAR_F);
        drv_max7219_config_reg(REG_DIGIT_1, SEG_CHAR_MINUS);
        drv_max7219_config_reg(REG_DIGIT_0, SEG_CHAR_DP);
    }
#endif
}