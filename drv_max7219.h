/**
 * @file drv_max7219.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief MAX7219ドライバ (for Arduino IDE)
 * @version 0.1
 * @date 2025-11-12
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef DRV_MAX7219_H
#define DRV_MAX7219_H

#include <stdint.h>
#include <SPI.h>

// ---------------------------------------------------
// [MAX7219 レジスタ]
#define REG_NO_OP               0x00
#define REG_DIGIT_0             0x01
#define REG_DIGIT_1             0x02
#define REG_DIGIT_2             0x03
#define REG_DIGIT_3             0x04
#define REG_DIGIT_4             0x05
#define REG_DIGIT_5             0x06
#define REG_DIGIT_6             0x07
#define REG_DIGIT_7             0x08
#define REG_DECODE_MODE         0x09
#define REG_BRIGHTNESS          0x0A
#define REG_SCAN_LIMIT          0x0B
#define REG_SHUTDOWN            0x0C
#define REG_DISPLAY_TEST        0x0F

// ---------------------------------------------------
// [定数]
#define SEG_DIGIT_CNT            7       // 7セグ桁数 8桁(0オリジン)

#define DECODE_NONE              0x00    // デコードモード = デコードなし
#define DECODE_CODE_B_FONT       0xFF    // デコードモード = コードBフォント

// コードBフォント
#define SEG_B_FONT_0               0x00 // 7セグ = '0'
#define SEG_B_FONT_1               0x01 // 7セグ = '1'
#define SEG_B_FONT_2               0x02 // 7セグ = '2'
#define SEG_B_FONT_3               0x03 // 7セグ = '3'
#define SEG_B_FONT_4               0x04 // 7セグ = '4'
#define SEG_B_FONT_5               0x05 // 7セグ = '5'
#define SEG_B_FONT_6               0x06 // 7セグ = '6'
#define SEG_B_FONT_7               0x07 // 7セグ = '7'
#define SEG_B_FONT_8               0x08 // 7セグ = '8'
#define SEG_B_FONT_9               0x09 // 7セグ = '9'
#define SEG_B_FONT_BAR             0x0A // 7セグ = '-'
#define SEG_B_FONT_E               0x0B // 7セグ = 'E'
#define SEG_B_FONT_H               0x0C // 7セグ = 'H'
#define SEG_B_FONT_L               0x0D // 7セグ = 'L'
#define SEG_B_FONT_P               0x0E // 7セグ = 'P'
#define SEG_B_FONT_BLANK           0x0F // 7セグ = 空欄

typedef struct {
    uint8_t reg_no_op;
    uint8_t reg_digit_0;
    uint8_t reg_digit_1;
    uint8_t reg_digit_2;
    uint8_t reg_digit_3;
    uint8_t reg_digit_4;
    uint8_t reg_digit_5;
    uint8_t reg_digit_6;
    uint8_t reg_digit_7;
    uint8_t reg_decode_mode;
    uint8_t reg_brightness;
    uint8_t reg_scan_limit;
    uint8_t reg_shutdown;
    uint8_t reg_display_test;
} max7219_reg_config_t;

void drv_max7219_7seg_init(max7219_reg_config_t *p_config);
void drv_max7219_write_7seg(uint8_t addr, uint8_t val);

#endif // DRV_MAX7219_H