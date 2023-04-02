#ifndef __LEDSUB_SPI_EXTERN_H_
#define __LEDSUB_SPI_EXTERN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    extern void UPDATE_GRAYDATA_B1();
    extern void UPDATE_GRAYDATA_B2();
    extern void UPDATE_BINARYDATA_B1();
    extern void UPDATE_BINARYDATA_B2();
    extern void HT_SPI_TRANSMIT(uint8_t data);
    extern void HT_SPI_CS(uint8_t state);
    extern void CLR_RAM();
    extern void CLR_BI_RAM();

#ifdef __cplusplus
}
#endif

#endif