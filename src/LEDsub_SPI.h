#ifndef _LEDSUB_SPI_H_
#define _LEDSUB_SPI_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef C_HT16D35_TYPE
#ifdef C_COLOR_TYPE
    void HT_HT16D35A_COLOR_INITIALIZATION();
#endif

#ifdef C_COLOR_TYPE
#ifdef C_MONO_TYPE
    void HT_HT16D35A_MONO1_INITIALIZATION();
#endif
#endif

#ifdef C_COLOR_TYPE
#ifdef C_MONO_TYPE
    void HT_HT16D35A_MONO2_INITIALIZATION();
#endif
#endif
#endif

    extern void HT_CLR_MONO_RAM_A();
    extern void HT_CASCADE_MODE_A();
    extern void HT_CONSTANT_CURRENT_A();
    extern void HT_DIRECT_PIN_A();
    extern void HT_GLOBAL_BRIGHTNESS_A();
    extern void HT_COM_OUTPUT_A();
    extern void HT_SEG_OUTPUT_A();
    extern void HT_UPDATE_GRAYDATA_A();
    extern void HT_UPDATE_BINARYDATA_A();
    extern void HT_RAM_UPDATE_A(uint8_t *data, uint16_t len);
    // extern void HT_SPI_TRANSMIT();
    extern void HT_LED_MODE_A();
    extern void HT_SCROLLING_STATUS_A();
    extern void HT_DIRECT_PIN_ROW27PWM_A();
    extern void HT_DIRECT_PIN_ROW26PWM_A();
    extern void HT_DIRECT_PIN_ROW25PWM_A();
    extern void HT_DIRECT_PIN_ROW24PWM_A();
    extern void HT_CLR_GRAYDATA_RAM_A();
    extern void HT_ModeOFF_NoScroll_NoDirectPin_A();
    extern void HT_FIREFLY_UPDATE_BR_A();

#ifdef __cplusplus
}
#endif

#endif
