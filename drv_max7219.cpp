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

void drv_max7219_write_7seg(uint8_t addr, uint8_t val)
{
    digitalWrite(SS, LOW);
    SPI.transfer(addr);
    SPI.transfer(val);
    digitalWrite(SS, HIGH);
}

void drv_max7219_7seg_init(max7219_reg_config_t *p_config)
{
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    drv_max7219_write_7seg(REG_DECODE_MODE,  p_config->reg_decode_mode);
    drv_max7219_write_7seg(REG_BRIGHTNESS,   p_config->reg_brightness);
    drv_max7219_write_7seg(REG_SCAN_LIMIT,   p_config->reg_scan_limit);
    drv_max7219_write_7seg(REG_SHUTDOWN,     p_config->reg_shutdown);
    drv_max7219_write_7seg(REG_DISPLAY_TEST, p_config->reg_display_test);
    drv_max7219_write_7seg(REG_DIGIT_7,      p_config->reg_digit_0);
    drv_max7219_write_7seg(REG_DIGIT_6,      p_config->reg_digit_1);
    drv_max7219_write_7seg(REG_DIGIT_5,      p_config->reg_digit_2);
    drv_max7219_write_7seg(REG_DIGIT_4,      p_config->reg_digit_3);
    drv_max7219_write_7seg(REG_DIGIT_3,      p_config->reg_digit_4);
    drv_max7219_write_7seg(REG_DIGIT_2,      p_config->reg_digit_5);
    drv_max7219_write_7seg(REG_DIGIT_1,      p_config->reg_digit_6);
    drv_max7219_write_7seg(REG_DIGIT_0,      p_config->reg_digit_7);
}