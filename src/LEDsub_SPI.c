#include "LEDsub_SPI.h"

#define C_HT16D35_SCROLLING_STATUS (0x20U)                // Scrolling control
#define C_HT16D35_SCROLLING_SPEED (0x21U)                 // Scrolling speed control
#define C_HT16D35_BINARY_GRAY_SCALE (0x31U)               // binary/gray scale
#define C_HT16D35_SCAN_NUM (0x32U)                        // scan number
#define C_HT16D35_GLOBAL_BLINKING (0x33U)                 // global blinking
#define C_HT16D35_CASCADE_MODE_SET (0x34U)                // cascade mode set Master Mode or Slave Mode select  XXXXX | MS[2:0]
#define C_HT16D35_SYS_CONTROL (0x35U)                     /// System oscillator on/off and display on/off control ,1 Byte data XXXXXX| FON | DON
#define C_HT16D35_CONSTANT_CURRENT_RATIO (0x36U)          // Constant current ratio select – 8 steps ,1 Byte data XXXX0 | CC[2:0]
#define C_HT16D35_GLOBAL_BRIGHTNESS (0x37U)               // global brightness control PWM adjustment 64 steps ,1 Byte data X | BC[6:0]
#define C_HT16D35_MODE_CONTROL (0x38U)                    /* mode control                                           \
                                                           * TSD EN | TSD SL | X | USEN | MKEN | UCEN | BKEN | FDEN \
                                                           * FDEN: FADE function on/off                             \
                                                           * BKEN: Blink function on/off                            \
                                                           * UCEN: UCOM function on/off                             \
                                                           * MKEN: Display mask on/off                              \
                                                           * USEN: USEG function on/off                             \
                                                           * TSDSL: Select auto control or user                     \
                                                           * control display on/off function when the               \
                                                           * over temperature protection is enabled                 \
                                                           * TSDEN: Thermal protect circuit on/off                  \
                                                           */
#define C_HT16D35_COM_OUTPUT (0x41U)                      // COM pin SW on/off ,1 Byte data
#define C_HT16D35_ROW_OUTPUT (0x42U)                      // COM pin SW on/off ,1 Byte data
#define C_HT16D35_DIRECTPIN_CTRL (0x43U)                  /* PW[24:27]: Direct PWM data output SW on/off                 \
                                                           * when ROW24~ROW27 pins are set as direct pins                \
                                                           * DR[24:27]: ROW24~ROW27 can be set as direct pin or row pin. \
                                                           */
#define C_HT16D35_DIRECTPIN_ROW27PWM (0x44U)              // PWM data for Direct ROW27
#define C_HT16D35_DIRECTPIN_ROW26PWM (0x45U)              // PWM data for Direct ROW26
#define C_HT16D35_DIRECTPIN_ROW25PWM (0x46U)              // PWM data for Direct ROW25
#define C_HT16D35_DIRECTPIN_ROW24PWM (0x47U)              // PWM data for Direct ROW24
#define C_HT16D35_READ_FLAG (0x70U)                       // Read Flag
#define C_HT16D35_READ_STATUS (0x71)                      // Read Status
#define C_HT16D35_WR_DIS_DATA (0x80U)                     // write display RAM operation
#define C_HT16D35_READ_DISPLAY_RAM (0x81U)                // Read Display RAM
#define C_HT16D35_WRITE_FADE_RAM_DATA (0x82U)             // Write fade RAM Data
#define C_HT16D35_READ_PARAMETERS_OF_FADE_RAM_DATA (0x83) // Read Parameters of Fade RAM Data
#define C_HT16D35_WRITE_UCOM_RAM_DATA (0x84U)             // Write UCOM RAM Data
#define C_HT16D35_READ_UCOM_DATA (0x85)                   // Read UCOM Data
#define C_HT16D35_WRITE_USEG_RAM_DATA (0x86)              // Write USEG RAM Data
#define C_HT16D35_USEG_CONTROL (0x86U)                    // USEG control
#define C_HT16D35_READ_USEG_CONTROL_DATA (0x87)           // Read USEG Control Data
#define C_HT16D35_MATRIX_MASKING (0x88U)                  // matrix display masking control
#define C_HT16D35_WRITE_MATRIX_MASKING_DATA (0x88)        // Write Matrix Masking Data
#define C_HT16D35_READ_MATRIX_MASKING_DATA (0x89)         // Read Matrix Masking Data
#define C_HT16D35_SOFTWARE_RESET (0x0CCU)                 // software reset

extern uint8_t g_u8v_ledram_count;
extern uint8_t g_u8v_graybuf1;
extern uint8_t g_u8v_graybuf2;
extern uint8_t g_u8v_binarybuf;
extern uint8_t g_u8v_spi_data;
extern uint8_t g_u8v_ledon_off;
extern uint8_t g_u8v_scan_num;
extern uint8_t g_u8v_binary_gray;
extern uint8_t g_u8v_com_output;
extern uint8_t g_u8v_seg_output1;
extern uint8_t g_u8v_seg_output2;
extern uint8_t g_u8v_seg_output3;
extern uint8_t g_u8v_seg_output4;
extern uint8_t g_u8v_constant_current;
extern uint8_t g_u8v_global_brightness;
extern uint8_t g_u8v_cascade_mode;
extern uint8_t g_u8v_mode_control;
extern uint8_t g_u8v_direct_pin;
extern uint8_t g_u8v_fade_control;
extern uint8_t g_u8v_scroll_status;
extern uint8_t g_u8v_mode_buffer1;
extern uint8_t g_u8v_mode_buffer2;
extern uint8_t g_u8v_scroll_buffer1;
extern uint8_t g_u8v_scroll_buffer2;
extern uint8_t g_u8v_dp_buffer1;
extern uint8_t g_u8v_dp_buffer2;
extern uint8_t g_u8v_dp_row27_pwm;
extern uint8_t g_u8v_dp_row26_pwm;
extern uint8_t g_u8v_dp_row25_pwm;
extern uint8_t g_u8v_dp_row24_pwm;
extern uint8_t g_u8v_gb_1;
extern uint8_t g_u8v_gb_2;
extern uint8_t g_u8v_firefly_cycletime;
extern uint8_t FG_IC2_ENABLE;
extern uint8_t fg_firefly_bk_cycle;
extern uint8_t fg_firefly_exit;
extern uint8_t fg_firefly_first;
extern uint8_t fg_firefly_bk_time;
extern uint8_t fg_firefly_fade;

extern void CLR_RAM();
extern void CLR_BI_RAM();

void HT_RAM_UPDATE_A(uint8_t *data, uint16_t len);
void HT_CLR_GRAYDATA_RAM_A(void);

void SOFTRESET_SETTING_A(void);
void LEDOFF_SETTING_A(void);
void LED_MODE0FF_SETTING_A(void);
void SCAN_NUM_SETTING_A(void);
void GRAY_MODE_SETTING_A(void);
void COM_SEG_SETTING_A(void);
void CURRENT_MAX_A(void);
void GLOBAL_BRIGHTNESS_MAX_A(void);
void CASCADE_M0M0_SETTING_A(void);
void LEDON_SETTING_A(void);
void SYS_LEDON_OFF(void);
void LED_MODE0FF_A(void);
void SCAN_NUM_A(void);
void BINARY_GRAY_MODE_A(void);
void COM_SEG_SETTING_A(void);
void COM_SEG_OUTPUT_A(void);
void ALL_FADE_A(void);
void ModeOFF_A(void);
void NO_SCROLLING_SETTING_A(void);
void NoScroll_NoDirectPin_A(void);
void NoScroll_A(void);
void NoDirectPin_A(void);
void NoDirectPin_A1(void);
void FIREFLY_EXIT(void);

#ifdef C_HT16D35_TYPE
extern void UPDATE_GRAYDATA_B1();
extern void UPDATE_GRAYDATA_B2();
extern void UPDATE_BINARYDATA_B1();
extern void UPDATE_BINARYDATA_B2();
#endif

//==================================================================
// Name:    HT_SPI_TRANSMIT
// Function: SPI data transmit
// Input:spi_tx_data
//==================================================================
extern void HT_SPI_TRANSMIT(uint8_t data);
extern void HT_SPI_CS(uint8_t state);

//==================================================================
// Name:    HT_HT16D35A_COLOR_INITIALIZATION
// Function: HT16D35A Colorful LED initial
// Input:
//==================================================================
#ifdef C_HT16D35_TYPE
#ifdef C_COLOR_TYPE
void HT_HT16D35A_COLOR_INITIALIZATION()
{
    SOFTRESET_SETTING_A();
    LEDOFF_SETTING_A();
    LED_MODE0FF_SETTING_A();
    NO_SCROLLING_SETTING_A();
    SCAN_NUM_SETTING_A();

    GRAY_MODE_SETTING_A();

    COM_SEG_SETTING_A();
    CURRENT_MAX_A();
    GLOBAL_BRIGHTNESS_MAX_A();
    CASCADE_M0M0_SETTING_A();

    HT_CLR_GRAYDATA_RAM_A();

    LEDON_SETTING_A();
    return;
}
#endif
#endif
//==================================================================
// Name:    HT_HT16D35A_MONO1_INITIALIZATION
// Function: HT16D35A MONO-BINARY LED initial
// Input:
//==================================================================
#ifdef C_HT16D35_TYPE
#ifdef C_COLOR_TYPE
#ifdef C_MONO_TYPE
void HT_HT16D35A_MONO1_INITIALIZATION()
{
    SOFTRESET_SETTING_A();
    LEDOFF_SETTING_A();
    LED_MODE0FF_SETTING_A();
    NO_SCROLLING_SETTING_A();
    SCAN_NUM_SETTING_A();

    BINARY_MODE_SETTING_A(1);

    COM_SEG_SETTING_A();
    CURRENT_MAX_A();
    GLOBAL_BRIGHTNESS_MAX_A();
    CASCADE_M0M0_SETTING_A();

    HT_CLR_MONO_RAM_A();

    LEDON_SETTING_A();
    return;
}
#endif
#endif
#endif
// ==================================================================
// Name:    HT_HT16D35A_MONO2_INITIALIZATION
// Function: HT16D35A MONO-GRAY LED initial
// Input:
// ==================================================================
#ifdef C_HT16D35_TYPE
#ifdef C_COLOR_TYPE
#if C_MONO_TYPE
void HT_HT16D35A_MONO2_INITIALIZATION()
{
    SOFTRESET_SETTING_A();
    LEDOFF_SETTING_A();
    LED_MODE0FF_SETTING_A();
    NO_SCROLLING_SETTING_A();
    SCAN_NUM_SETTING_A();
    GRAY_MODE_SETTING_A();
    COM_SEG_SETTING_A();
    CURRENT_MAX_A();
    GLOBAL_BRIGHTNESS_MAX_A();
    CASCADE_M0M0_SETTING_A();
    HT_CLR_GRAYDATA_RAM_A();
    LEDON_SETTING_A();
    return;
}
#endif
#endif
#endif

// ==================================================================
// Name:    SOFTRESET_SETTING_A
// Function: HT16D35A soft reset
// Input:
// ==================================================================
void SOFTRESET_SETTING_A()
{
    HT_SPI_CS(0);
    HT_SPI_TRANSMIT(C_HT16D35_SOFTWARE_RESET); // software reset
    HT_SPI_CS(1);
    return;
}

// ==================================================================
// Name:    LEDON_SETTING_A/_LEDOFF_SETTING_A
// Function: HT16D35A LED on/off
// Input:
// ==================================================================
void LEDON_SETTING_A()
{
    g_u8v_ledon_off = 0x03; // sys enable & LED on

    HT_SPI_CS(0);
    SYS_LEDON_OFF();
    HT_SPI_CS(1);
    return;
}

void LEDOFF_SETTING_A()
{
    g_u8v_ledon_off = 0x02; // sys enable & LED off

    HT_SPI_CS(0);
    SYS_LEDON_OFF();
    HT_SPI_CS(1);
    return;
}

void SYS_LEDON_OFF()
{
    HT_SPI_TRANSMIT(C_HT16D35_SYS_CONTROL); // system control
    HT_SPI_TRANSMIT(g_u8v_ledon_off);
    return;
}

// ==================================================================
// Name:    LED_MODE0FF_SETTING_A
// Function: disable HT16D35A mode off
// Input:
// ==================================================================
void LED_MODE0FF_SETTING_A()
{
    HT_SPI_CS(0);
    LED_MODE0FF_A();
    HT_SPI_CS(1);
    return;
}

void LED_MODE0FF_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_MODE_CONTROL); // mode control
    HT_SPI_TRANSMIT(0x00);
    return;
}

void HT_LED_MODE_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_MODE_CONTROL); // mode control
    HT_SPI_TRANSMIT(g_u8v_mode_control);
    return;
}
// ==================================================================
// Name:    NO_SCROLLING_SETTING_A
// Function: disable HT16D35A scrolling mode disable
// Input:
// ==================================================================
void NO_SCROLLING_SETTING_A()
{
    g_u8v_scroll_status = 0; // no scrolling
    HT_SPI_CS(0);
    HT_SCROLLING_STATUS_A();
    HT_SPI_CS(1);
    return;
}
void HT_SCROLLING_STATUS_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_SCROLLING_STATUS);
    HT_SPI_TRANSMIT(g_u8v_scroll_status);
    return;
}

// ==================================================================
// Name:    SCAN_NUM_SETTING_A
// Function: HT16D35A scan number setting
// Input:
// ==================================================================
void SCAN_NUM_SETTING_A()
{
    g_u8v_scan_num = 0x07;

    HT_SPI_CS(0);
    SCAN_NUM_A();
    HT_SPI_CS(1);
    return;
}

void SCAN_NUM_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_SCAN_NUM); // scan number
    HT_SPI_TRANSMIT(g_u8v_scan_num);     // 1/8 Duty
    return;
}

// ==================================================================
// Name:    GRAY_MODE_SETTING_A/_BINARY_MODE_SETTING_A
// Function: HT16D35A gray mode/binary mode select
// Input:
// ==================================================================
void GRAY_MODE_SETTING_A()
{
    g_u8v_binary_gray = 0;

    HT_SPI_CS(0);
    BINARY_GRAY_MODE_A();
    HT_SPI_CS(1);
    return;
}

void BINARY_MODE_SETTING_A()
{
    g_u8v_binary_gray = 1;

    HT_SPI_CS(0);
    BINARY_GRAY_MODE_A();
    HT_SPI_CS(1);
    return;
}

void BINARY_GRAY_MODE_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_BINARY_GRAY_SCALE); // binary/gray scale
    HT_SPI_TRANSMIT(g_u8v_binary_gray);
    return;
}

// ==================================================================
// Name:    COM_SEG_SETTING_A
// Function: HT16D35A window masking setting
// Input:
// ==================================================================
void COM_SEG_SETTING_A()
{
    HT_SPI_CS(0);
    COM_SEG_OUTPUT_A();
    HT_SPI_CS(1);
    return;
}

void COM_SEG_OUTPUT_A()
{
    g_u8v_com_output = 0xff;
    g_u8v_seg_output1 = 0xff;
    g_u8v_seg_output2 = 0xff;
    g_u8v_seg_output3 = 0xff;
    g_u8v_seg_output4 = 0xff;
    HT_COM_OUTPUT_A();
    HT_SEG_OUTPUT_A();
    return;
}

void HT_COM_OUTPUT_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_COM_OUTPUT); // COM output
    HT_SPI_TRANSMIT(g_u8v_com_output);     // all COM output pins turn on
    return;
}

void HT_SEG_OUTPUT_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_ROW_OUTPUT); // ROW output
    HT_SPI_TRANSMIT(g_u8v_seg_output1);    // all ROW output pins turn on
    HT_SPI_TRANSMIT(g_u8v_seg_output2);
    HT_SPI_TRANSMIT(g_u8v_seg_output3);
    HT_SPI_TRANSMIT(g_u8v_seg_output4);
    return;
}

// ==================================================================
// Name:    CURRENT_SETTING_A
// Function: HT16D35A constant current setting
// Input:
// ==================================================================
void CURRENT_MAX_A()
{
    g_u8v_constant_current = 0x07;

    HT_SPI_CS(0);
    HT_CONSTANT_CURRENT_A();
    HT_SPI_CS(1);
    return;
}

void HT_CONSTANT_CURRENT_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_CONSTANT_CURRENT_RATIO); // constant current adjustment
    HT_SPI_TRANSMIT(g_u8v_constant_current);           // 16/16 X IROWMAX
    return;
}

// ==================================================================
// Name:    GLOBAL_BRIGHTNESS_MAX_A
// Function: HT16D35A constant current setting
// Input:
// ==================================================================
void GLOBAL_BRIGHTNESS_MAX_A()
{
    g_u8v_global_brightness = 0x40;

    HT_SPI_CS(0);
    HT_GLOBAL_BRIGHTNESS_A();
    HT_SPI_CS(1);
    return;
}

void HT_GLOBAL_BRIGHTNESS_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_GLOBAL_BRIGHTNESS); // global brightness
    HT_SPI_TRANSMIT(g_u8v_global_brightness);     // duty = 64/64
    return;
}

// ==================================================================
// Name:    CASCADE_M0M0_SETTING_A
// Function: HT16D35A cascade mode setting:M0M0
// Input:
// ==================================================================
void CASCADE_M0M0_SETTING_A()
{
    g_u8v_cascade_mode = 0;
    HT_SPI_CS(0);
    HT_CASCADE_MODE_A();
    HT_SPI_CS(1);
    return;
}

void HT_CASCADE_MODE_A()
{

    HT_SPI_TRANSMIT(C_HT16D35_CASCADE_MODE_SET); // cascade mode set
    HT_SPI_TRANSMIT(g_u8v_cascade_mode);
    return;
}
/**********************************************************************
 * @brief HT16D35A direct pin control
 **********************************************************************/
void HT_DIRECT_PIN_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_DIRECTPIN_CTRL); //; direct pin control
    HT_SPI_TRANSMIT(g_u8v_direct_pin);         //
}

void HT_DIRECT_PIN_ROW27PWM_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_DIRECTPIN_ROW27PWM); //; direct pin ROW27 PWM
    HT_SPI_TRANSMIT(g_u8v_dp_row27_pwm);           //
}

void HT_DIRECT_PIN_ROW26PWM_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_DIRECTPIN_ROW26PWM); //; direct pin ROW26 PWM
    HT_SPI_TRANSMIT(g_u8v_dp_row26_pwm);           //
}

void HT_DIRECT_PIN_ROW25PWM_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_DIRECTPIN_ROW25PWM); //; direct pin ROW25 PWM
    HT_SPI_TRANSMIT(g_u8v_dp_row25_pwm);           //
}

void HT_DIRECT_PIN_ROW24PWM_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_DIRECTPIN_ROW24PWM); //; direct pin ROW24 PWM
    HT_SPI_TRANSMIT(g_u8v_dp_row24_pwm);           //
}

//==================================================================
// Name:    CLR_FADE_RAM_A
// Function: clear HT16D35A FADE RAM
// Input:
//==================================================================
void CLR_FADE_RAM_A()
{
    g_u8v_mode_control = 0x01; //
    g_u8v_fade_control = 0;

    HT_SPI_CS(0);
    ALL_FADE_A();
    HT_SPI_CS(1);
    HT_SPI_CS(0);
    HT_LED_MODE_A();
    HT_SPI_CS(1);
}

void ALL_FADE_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_WRITE_FADE_RAM_DATA);
    HT_SPI_TRANSMIT(0x00);

    g_u8v_ledram_count = 224;
    while ((--g_u8v_ledram_count) != 0)
    {
        HT_SPI_TRANSMIT(g_u8v_fade_control);
    }
}

//==================================================================
// Name:    HT_CLR_GRAYDATA_RAM_A/_HT_CLR_MONO_RAM_A
// Function: clear HT16D35A gray/binary data RAM
// Input:
//==================================================================
void HT_CLR_GRAYDATA_RAM_A()
{
    CLR_RAM();
    HT_SPI_CS(0);
    HT_UPDATE_GRAYDATA_A();
    HT_SPI_CS(1);
    return;
}

void HT_UPDATE_GRAYDATA_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_WR_DIS_DATA);
    HT_SPI_TRANSMIT(0x00);
    HT_RAM_UPDATE_A(&g_u8v_graybuf1, 112);
    HT_RAM_UPDATE_A(&g_u8v_graybuf2, 112);
}

void HT_UPDATE_BINARYDATA_A()
{
    HT_SPI_TRANSMIT(C_HT16D35_WR_DIS_DATA);
    HT_SPI_TRANSMIT(0x00);
    HT_RAM_UPDATE_A(&g_u8v_binarybuf, 28);
}

void HT_CLR_MONO_RAM_A()
{
    CLR_BI_RAM();
    HT_SPI_CS(0);
    HT_UPDATE_BINARYDATA_A();
    HT_SPI_CS(1);
}

void HT_RAM_UPDATE_A(uint8_t *data, uint16_t len)
{
    for (int i = 0; i < len; i++)
    {
        HT_SPI_TRANSMIT(data[i]);
    }
}

void NO_DIRECT_PIN_A()
{
    g_u8v_direct_pin = 0;
    HT_SPI_CS(0);
    HT_DIRECT_PIN_A();
    HT_SPI_CS(1);
    return;
}

void HT_ModeOFF_NoScroll_NoDirectPin_A()
{
    if (g_u8v_mode_buffer1 != 0)
        ModeOFF_A();
    if (g_u8v_mode_buffer1 != 0)
        ModeOFF_A();
    NoScroll_NoDirectPin_A();
}

void ModeOFF_A()
{
    LED_MODE0FF_SETTING_A();
}
void NoScroll_NoDirectPin_A()
{
    if (g_u8v_scroll_buffer1 != 0)
        NoScroll_A();
    if (g_u8v_scroll_buffer2 != 0)
        NoScroll_A();
    NoDirectPin_A1();
}
void NoScroll_A()
{
    NO_SCROLLING_SETTING_A();
}
void NoDirectPin_A1()
{
    if (g_u8v_dp_buffer1 != 0)
        NoDirectPin_A();
    if (g_u8v_dp_buffer2 != 0)
        NoDirectPin_A();
    return;
}
void NoDirectPin_A()
{
    NO_DIRECT_PIN_A();
    return;
}

/**********************************************************************
 * 控制 LED 灯的亮度和循环时间
 *
 **********************************************************************/
void HT_FIREFLY_UPDATE_BR_A()
{
    g_u8v_global_brightness = g_u8v_gb_1; //
    HT_SPI_CS(0);
    HT_GLOBAL_BRIGHTNESS_A(); // IC1 GLOBAL BRIGHTNESS
    HT_SPI_CS(1);

    g_u8v_global_brightness = g_u8v_gb_2;

    if (fg_firefly_bk_cycle == 0)
        return;

    fg_firefly_bk_cycle = 0;

    if (g_u8v_firefly_cycletime == 0)
        FIREFLY_EXIT();
    if ((--g_u8v_firefly_cycletime) != 0)
        return;
}

void FIREFLY_EXIT()
{
    fg_firefly_exit = 1;
    fg_firefly_first = 0;
    fg_firefly_bk_time = 0;
    fg_firefly_fade = 0;
    return;
}
