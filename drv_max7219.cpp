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

void drv_max7219_7seg_init(void)
{
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    drv_max7219_write_7seg(REG_DECODE_MODE,  DECODE_CODE_B_FONT);
    drv_max7219_write_7seg(REG_BRIGHTNESS,   0x05);
    drv_max7219_write_7seg(REG_SCAN_LIMIT,   SEG_DIGIT_CNT);
    drv_max7219_write_7seg(REG_SHUTDOWN,     1);
    drv_max7219_write_7seg(REG_DISPLAY_TEST, 0);

    // 7セグ8桁に「01234567」を表示
    drv_max7219_write_7seg(REG_DIGIT_7, 0x00);
    drv_max7219_write_7seg(REG_DIGIT_6, 0x01);
    drv_max7219_write_7seg(REG_DIGIT_5, 0x02);
    drv_max7219_write_7seg(REG_DIGIT_4, 0x03);
    drv_max7219_write_7seg(REG_DIGIT_3, 0x04);
    drv_max7219_write_7seg(REG_DIGIT_2, 0x05);
    drv_max7219_write_7seg(REG_DIGIT_1, 0x06);
    drv_max7219_write_7seg(REG_DIGIT_0, 0x07);
}