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

void setup()
{
#ifdef DEBUG_SEG_PRINT
    Serial.begin(115200);
#endif

    drv_max7219_7seg_init(NULL);

#ifdef DEBUG_SEG_TEST
    drv_max7219_7seg_test();
#endif
}

void loop()
{
    drv_max7219_7seg_animation();
}