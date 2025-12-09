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

max7219_reg_config_t g_config;

const uint8_t g_seg_digit[8] = {
    REG_DIGIT_7,
    REG_DIGIT_6,
    REG_DIGIT_5,
    REG_DIGIT_4,
    REG_DIGIT_3,
    REG_DIGIT_2,
    REG_DIGIT_1,
    REG_DIGIT_0
};

typedef struct {
    char c;
    uint8_t font;
} seg_char_t;

const seg_char_t g_seg_font_tbl[40] = {
    {'0', SEG_CHAR_0},
    {'1', SEG_CHAR_1},
    {'2', SEG_CHAR_2},
    {'3', SEG_CHAR_3},
    {'4', SEG_CHAR_4},
    {'5', SEG_CHAR_5},
    {'6', SEG_CHAR_6},
    {'7', SEG_CHAR_7},
    {'8', SEG_CHAR_8},
    {'9', SEG_CHAR_9},
    {'A', SEG_CHAR_A},
    {'B', SEG_CHAR_B},
    {'C', SEG_CHAR_C},
    {'D', SEG_CHAR_D},
    {'E', SEG_CHAR_E},
    {'F', SEG_CHAR_F},
    {'G', SEG_CHAR_G},
    {'H', SEG_CHAR_H},
    {'I', SEG_CHAR_I},
    {'J', SEG_CHAR_J},
    {'K', SEG_CHAR_K},
    {'L', SEG_CHAR_L},
    {'N', SEG_CHAR_N},
    {'M', SEG_CHAR_M},
    {'O', SEG_CHAR_O},
    {'P', SEG_CHAR_P},
    {'Q', SEG_CHAR_Q},
    {'R', SEG_CHAR_R},
    {'S', SEG_CHAR_S},
    {'T', SEG_CHAR_T},
    {'U', SEG_CHAR_U},
    {'V', SEG_CHAR_V},
    {'W', SEG_CHAR_W},
    {'X', SEG_CHAR_X},
    {'Y', SEG_CHAR_Y},
    {'Z', SEG_CHAR_Z},
    {'-', SEG_CHAR_MINUS},
    {'.', SEG_CHAR_DP},
    {' ', SEG_CHAR_BLANK},
    {'\0', SEG_CHAR_BLANK}
};
const uint8_t SEG_FONT_TBL_SIZE = sizeof(g_seg_font_tbl) / sizeof(g_seg_font_tbl[0]);

static void seg_char_test(uint32_t delay_ms);
static void seg_animation_test(uint32_t delay_ms);
// ---------------------------------------------------
static void seg_char_test(uint32_t delay_ms)
{
    // 「01234567」
    drv_max7219_show_char((uint8_t *)"01234567");
    delay(delay_ms);

    // 「ABCDEFGH」
    drv_max7219_show_char((uint8_t *)"ABCDEFGH");
    delay(delay_ms);

    // 「IJKLNMOP」
    drv_max7219_show_char((uint8_t *)"IJKLNMOP");
    delay(delay_ms);

    // 「QRSTU」
    drv_max7219_show_char((uint8_t *)"QRSTU");
    delay(delay_ms);

    // 「VWXYZ-.」
    drv_max7219_show_char((uint8_t *)"VWXYZ-.");
    delay(delay_ms);
}

static void seg_animation_test(uint32_t delay_ms)
{
    // 上丸、下丸交互
    g_config.reg_decode_mode = DECODE_NONE;
    drv_max7219_config_reg(REG_DECODE_MODE, g_config.reg_decode_mode);
    drv_max7219_config_reg(REG_DIGIT_7, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_6, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_5, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_4, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_3, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_2, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_1, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_0, SEG_CHAR_LM);
    delay(delay_ms);
    drv_max7219_config_reg(REG_DIGIT_7, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_6, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_5, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_4, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_3, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_2, SEG_CHAR_UM);
    drv_max7219_config_reg(REG_DIGIT_1, SEG_CHAR_LM);
    drv_max7219_config_reg(REG_DIGIT_0, SEG_CHAR_UM);
    delay(delay_ms);
}

// ---------------------------------------------------
void drv_max7219_config_reg(uint8_t addr, uint8_t val)
{
    digitalWrite(SS, LOW);
    SPI.transfer(addr);
    SPI.transfer(val);
    digitalWrite(SS, HIGH);
}

void drv_max7219_show_num(uint32_t val)
{
    uint8_t d = 0;
    uint8_t i = 0;
    uint32_t v = 0;
    uint8_t idx = 0;
    uint8_t digits[8];

    if(g_config.reg_decode_mode != DECODE_CODE_B_FONT) {
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

void drv_max7219_show_char(uint8_t *p_buf)
{
    uint8_t q, i;

    if(strlen((char *)p_buf) > 8) {
        return;
    }

    g_config.reg_decode_mode = DECODE_NONE;
    drv_max7219_config_reg(REG_DECODE_MODE, g_config.reg_decode_mode);

    for(i = 0; i < 8; i++)
    {
        drv_max7219_config_reg(REG_DIGIT_7 - i, SEG_CHAR_BLANK);
        for(q = 0; q < SEG_FONT_TBL_SIZE; q++)
        {
            if(p_buf[i] == g_seg_font_tbl[q].c)
            {
                drv_max7219_config_reg(REG_DIGIT_7 - i, g_seg_font_tbl[q].font);
#ifdef DEBUG_SEG_PRINT
                Serial.print("Digit ");
                Serial.print(7 - i);
                Serial.print(" : ");
                Serial.print((char)p_buf[i]);
                Serial.println();
#endif
            }
        }
    }
}

void drv_max7219_7seg_init(max7219_reg_config_t *p_config)
{
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);

    if(p_config == NULL) {
        g_config.reg_decode_mode = DECODE_NONE;
        g_config.reg_brightness = 0x05;
        g_config.reg_scan_limit = SEG_DIGIT_CNT;
        g_config.reg_shutdown = 1;
        g_config.reg_display_test = 0;
    } else {
        g_config = *p_config;
    }

    drv_max7219_config_reg(REG_BRIGHTNESS,   g_config.reg_brightness);
    drv_max7219_config_reg(REG_SCAN_LIMIT,   g_config.reg_scan_limit);
    drv_max7219_config_reg(REG_SHUTDOWN,     g_config.reg_shutdown);
    drv_max7219_config_reg(REG_DISPLAY_TEST, g_config.reg_display_test);
    drv_max7219_show_char((uint8_t *)"--------");
    drv_max7219_config_reg(REG_DECODE_MODE,  g_config.reg_decode_mode);
}

void drv_max7219_7seg_test(void)
{
    uint8_t i;

    seg_char_test(300);

    for(i = 0; i < 6; i++)
    {
        seg_animation_test(300);
    }
}

void drv_max7219_7seg_animation(void)
{
    seg_animation_test(300);
}