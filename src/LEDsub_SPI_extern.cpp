/* include ------------------------------------------------------------------*/
#include "LEDsub_SPI_extern.h"
#include "Arduino.h"

/* define -----------------------------------------------------------*/

/* variables --------------------------------------------------------*/
uint8_t g_u8v_ledram_count;
uint8_t g_u8v_graybuf1;
uint8_t g_u8v_graybuf2;
uint8_t g_u8v_binarybuf;
uint8_t g_u8v_spi_data;
uint8_t g_u8v_ledon_off;
uint8_t g_u8v_scan_num;
uint8_t g_u8v_binary_gray;
uint8_t g_u8v_com_output;
uint8_t g_u8v_seg_output1;
uint8_t g_u8v_seg_output2;
uint8_t g_u8v_seg_output3;
uint8_t g_u8v_seg_output4;
uint8_t g_u8v_constant_current;
uint8_t g_u8v_global_brightness;
uint8_t g_u8v_cascade_mode;
uint8_t g_u8v_mode_control;
uint8_t g_u8v_direct_pin;
uint8_t g_u8v_fade_control;
uint8_t g_u8v_scroll_status;
uint8_t g_u8v_mode_buffer1;
uint8_t g_u8v_mode_buffer2;
uint8_t g_u8v_scroll_buffer1;
uint8_t g_u8v_scroll_buffer2;
uint8_t g_u8v_dp_buffer1;
uint8_t g_u8v_dp_buffer2;
uint8_t g_u8v_dp_row27_pwm;
uint8_t g_u8v_dp_row26_pwm;
uint8_t g_u8v_dp_row25_pwm;
uint8_t g_u8v_dp_row24_pwm;
uint8_t g_u8v_gb_1;
uint8_t g_u8v_gb_2;
uint8_t g_u8v_firefly_cycletime;
uint8_t FG_IC2_ENABLE;
uint8_t fg_firefly_bk_cycle;
uint8_t fg_firefly_exit;
uint8_t fg_firefly_first;
uint8_t fg_firefly_bk_time;
uint8_t fg_firefly_fade;

/* function prototype ------------------------------------------------*/
void UPDATE_GRAYDATA_B1()
{
    Serial.printf("%s called\n", __func__);
}
void UPDATE_GRAYDATA_B2()
{
    Serial.printf("%s called\n", __func__);
}
void UPDATE_BINARYDATA_B1()
{
    Serial.printf("%s called\n", __func__);
}
void UPDATE_BINARYDATA_B2()
{
    Serial.printf("%s called\n", __func__);
}
void HT_SPI_TRANSMIT(uint8_t data)
{
    Serial.printf("spi send :%x\n", data);
}
void HT_SPI_CS(uint8_t state)
{
    Serial.printf("spi cs :%d\n", state);
}
void CLR_RAM()
{
    Serial.printf("%s called\n", __func__);
}

void CLR_BI_RAM()
{
    Serial.printf("%s called\n", __func__);
}
