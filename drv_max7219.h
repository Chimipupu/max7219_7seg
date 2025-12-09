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

// ---------------------------------------------------
// [デコード = コードBフォント]
#define SEG_B_FONT_0             0x00 // 7セグ = '0'
#define SEG_B_FONT_1             0x01 // 7セグ = '1'
#define SEG_B_FONT_2             0x02 // 7セグ = '2'
#define SEG_B_FONT_3             0x03 // 7セグ = '3'
#define SEG_B_FONT_4             0x04 // 7セグ = '4'
#define SEG_B_FONT_5             0x05 // 7セグ = '5'
#define SEG_B_FONT_6             0x06 // 7セグ = '6'
#define SEG_B_FONT_7             0x07 // 7セグ = '7'
#define SEG_B_FONT_8             0x08 // 7セグ = '8'
#define SEG_B_FONT_9             0x09 // 7セグ = '9'
#define SEG_B_FONT_BAR           0x0A // 7セグ = '-'
#define SEG_B_FONT_E             0x0B // 7セグ = 'E'
#define SEG_B_FONT_H             0x0C // 7セグ = 'H'
#define SEG_B_FONT_L             0x0D // 7セグ = 'L'
#define SEG_B_FONT_P             0x0E // 7セグ = 'P'
#define SEG_B_FONT_BLANK         0x0F // 7セグ = 空欄

// ---------------------------------------------------
// [デコードなし]
// NOTE: フリーフォントの「DSEG」を採用
// デコードなし(8bitデータ = DP,A,B,C,D,E,F,Gの順)
// ビット: 0x80=DP, 0x40=A, 0x20=B, 0x10=C, 0x08=D, 0x04=E, 0x02=F, 0x01=G
#define SEG_BIT_DP               0x80
#define SEG_BIT_A                0x40
#define SEG_BIT_B                0x20
#define SEG_BIT_C                0x10
#define SEG_BIT_D                0x08
#define SEG_BIT_E                0x04
#define SEG_BIT_F                0x02
#define SEG_BIT_G                0x01

#define SEG_CHAR_0               0x7E // '0' = ABCDEF
#define SEG_CHAR_1               0x30 // '1' = BC
#define SEG_CHAR_2               0x6D // '2' = ABGED
#define SEG_CHAR_3               0x79 // '3' = ABCDG
#define SEG_CHAR_4               0x33 // '4' = FGBC
#define SEG_CHAR_5               0x5B // '5' = AFGCD
#define SEG_CHAR_6               0x5F // '6' = AFEDCG
#define SEG_CHAR_7               0x70 // '7' = ABC
#define SEG_CHAR_8               0x7F // '8' = ABCDEFG
#define SEG_CHAR_9               0x7B // '9' = ABCDFG
#define SEG_CHAR_A               0x77 // 'A' = ABCEFG
#define SEG_CHAR_B               0x1F // 'b' = CDEFG
#define SEG_CHAR_C               0x4E // 'C' = AFED
#define SEG_CHAR_D               0x3D // 'd' = BCDEG
#define SEG_CHAR_E               0x4F // 'E' = AFEDG
#define SEG_CHAR_F               0x47 // 'F' = AFEG
#define SEG_CHAR_G               0x5E // 'G' = AFEDC
#define SEG_CHAR_H               0x17 // 'H' = CEFG
#define SEG_CHAR_I               0x06 // 'I' = EF
#define SEG_CHAR_J               0x3C // 'J' = BCDE
#define SEG_CHAR_K               0x57 // 'K' = ACEFG
#define SEG_CHAR_L               0x0E // 'L' = DEF
#define SEG_CHAR_N               0x76 // 'N' = ABCEF
#define SEG_CHAR_M               0x15 // 'M' = CEG
#define SEG_CHAR_O               0x1D // 'O' = CDEG
#define SEG_CHAR_P               0x67 // 'P' = ABEFG
#define SEG_CHAR_Q               0x73 // 'Q' = ABCFG
#define SEG_CHAR_R               0x05 // 'r' = EG
#define SEG_CHAR_S               0x1B // 'S' = CDFG
#define SEG_CHAR_T               0x0F // 'T' = DEFG
#define SEG_CHAR_U               0x1C // 'U' = CDE
#define SEG_CHAR_V               0x3E // 'V' = BCDEF
#define SEG_CHAR_W               0x2A // 'W' = BDF
#define SEG_CHAR_X               0x37 // 'X' = BCEFG
#define SEG_CHAR_Y               0x3B // 'Y' = BCDFG
#define SEG_CHAR_Z               0x6C // 'Z' = ABDE
#define SEG_CHAR_MINUS           0x01 // '-' = G
#define SEG_CHAR_DP              0x80 // '.'(ドット) = DP
#define SEG_CHAR_UM              0x63 // 上丸 = ABFG
#define SEG_CHAR_LM              0x1D // 下丸 = CDEG
#define SEG_CHAR_BLANK           0x00 // 空白
// ---------------------------------------------------
typedef struct {
    uint8_t reg_no_op;
    uint8_t reg_decode_mode;
    uint8_t reg_brightness;
    uint8_t reg_scan_limit;
    uint8_t reg_shutdown;
    uint8_t reg_display_test;
} max7219_reg_config_t;
// ---------------------------------------------------
void drv_max7219_config_reg(uint8_t addr, uint8_t val);
void drv_max7219_display_7seg(uint32_t val);
void drv_max7219_7seg_init(max7219_reg_config_t *p_config);
void drv_max7219_7seg_test(void);

#endif // DRV_MAX7219_H