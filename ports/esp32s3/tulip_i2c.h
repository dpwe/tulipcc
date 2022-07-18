// i2c.h

#ifndef _TULIPI2C_H_
#define _TULIPI2C_H_
//static const char *TAG = "TULIP_I2C";


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"


typedef void* i2c_bus_handle_t;
//static uint16_t volume;
typedef enum {
    TOUCH_EVT_RELEASE = 0x0,
    TOUCH_EVT_PRESS   = 0x1,
} touch_evt_t;

typedef struct {
    uint8_t touch_event;
    uint8_t touch_point;
    uint16_t curx[5];
    uint16_t cury[5];
} touch_info_t;

typedef struct {
    int reversed;
} ft5x06_cfg_t;

typedef struct {
    i2c_bus_handle_t bus;
    uint8_t dev_addr;
    bool xy_swap;
    uint16_t x_size;
    uint16_t y_size;
    //touch_info_t tch_info;
} ft5x06_dev_t;
typedef void*  ft5x06_handle_t;


void touch_start();
i2c_bus_handle_t iot_i2c_bus_create(i2c_port_t port, i2c_config_t* conf);
esp_err_t iot_i2c_bus_delete(i2c_bus_handle_t bus);
esp_err_t iot_i2c_bus_cmd_begin(i2c_bus_handle_t bus, i2c_cmd_handle_t cmd, portBASE_TYPE ticks_to_wait);
esp_err_t wm8960_init();
void wm8960_set_vol(uint16_t vol, uint8_t module);
uint16_t wm8960_get_vol();
esp_err_t wm8960_set_mute(bool mute);
esp_err_t ft5x06_read(ft5x06_handle_t dev, uint8_t start_addr,
        uint8_t read_num, uint8_t *data_buf);
esp_err_t ft5x06_write(ft5x06_handle_t dev, uint8_t start_addr,
        uint8_t write_num, uint8_t *data_buf);
esp_err_t ft5x06_touch_report(ft5x06_handle_t dev, touch_info_t* ifo);
ft5x06_handle_t ft5x06_create(i2c_bus_handle_t bus, uint16_t dev_addr);
esp_err_t ft5x06_init(ft5x06_handle_t dev, ft5x06_cfg_t * cfg);




#define CHECK(x) do { esp_err_t _; if ((_ = x) != ESP_OK) return __; } while (0)
#define CHECK_ARG(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)

#define R0_LEFT_INPUT_VOLUME_ADR 0x00
#define R1_RIGHT_INPUT_VOLUME_ADR 0x01
#define R2_LOUT1_VOLUME_ADR 0x02
#define R3_ROUT1_VOLUME_ADR 0x03
#define R4_CLOCKING_1_ADR 0x04
#define R5_ADC_DAC_CONTROL_CTR1_ADR 0x05
#define R6_ADC_DAC_CONTROL_CTR2_ADR 0x06
#define R7_AUDIO_INTERFACE_1_ADR 0x07
#define R8_CLOCKING_2_ADR 0x08
#define R10_LEFT_DAC_VOLUME_ADR 0x09
#define R11_RIGHT_DAC_VOLUME_ADR 0x0A
#define R15_RESET_ADR 0x0F
#define R16_3D_CONTROL_ADR 0x10
#define R17_ALC1_ADR 0x11
#define R18_ALC2_ADR 0x12
#define R19_ALC3_ADR 0x13
#define R20_NOISE_GATE_ADR 0x14
#define R21_LEFT_ADC_VOLUME_ADR 0x15
#define R22_RIGHT_ADC_VOLUME_ADR 0x16
#define R23_ADDITIONAL_CONTROL_1_ADR 0x17
#define R24_ADDITIONAL_CONTROL_2_ADR 0x18
#define R25_PWR_MGMT_1_ADR 0x19
#define R26_PWR_MGMT_2_ADR 0x1A
#define R27_ADDITIONAL_CONTROL_3_ADR 0x1B
#define R28_ANTI_POP_1_ADR 0x1C
#define R29_ANTI_POP_2_ADR 0x1D
#define R32_ADCL_SIGNAL_PATH 0x20
#define R33_ADCR_SIGNAL_PATH 0x21 
#define R34_LEFT_OUT_MIX_2 0x22 
#define R37_RIGHT_OUT_MIX_2 0x23 
#define R38_MONO_OUT_MIX_1 0x26
#define R39_MONO_OUT_MIX_2 0x27 
#define R40_LOUT2_VOLUME 0x28 
#define R41_ROUT2_VOLUME 0x29
#define R42_MONOOUT_VOLUME 0x2A
#define R43_INPUT_BOOST_MIXER_1 0x2B
#define R44_INPUT_BOOST_MIXER_2 0x2C
#define R45_BYPASS_1 0x2D
#define R46_BYPASS_2 0x2E
#define R47_PWR_MGMT_3 0x2F
#define R48_ADDITONAL_CTRL_4 0x30
#define R49_CLASS_D_CTRL_1 0x31 
#define R51_CLASS_D_CTRL_3 0x33


#define CODEC_ADDR  0x1a
#define SDA_PIN  18
#define SCL_PIN  17
#define I2C_BUS_NO 0
#define ACK_CHECK_EN  0
#define ACK_CHECK_DIS 0
#define ACK_VAL       0
#define NACK_VAL      1

#define _MAX_VOLUME_ADC (0xFF)
#define _MAX_VOLUME_DAC  (0xFF)
#define _MAX_VOLUME_HEADPHONE  (0x7F)
#define _MAX_VOLUME_LINEIN  (0x3F)
#define _MAX_VOLUME_SPEAKER (0x7F)
#define _LDAC  (0xA)
#define _LOUT1 (0x2)
#define _LOUT2 (0x28)



#define FT5X06_ADDR    (0x38)
#define SCREEN_XSIZE       (H_RES)
#define SCREEN_YSIZE       (V_RES)

#define WRITE_BIT          (I2C_MASTER_WRITE)       /*!< I2C master write */
#define READ_BIT           (I2C_MASTER_READ)        /*!< I2C master read */
//#define ACK_CHECK_EN       0x1                      /*!< I2C master will check ack from slave*/
//#define ACK_CHECK_DIS      0x0                      /*!< I2C master will not check ack from slave */
//#define ACK_VAL            0x0                      /*!< I2C ack value */
//#define NACK_VAL           0x1                      /*!< I2C nack value */

#define    FT5X0X_REG_THGROUP                0x80   /* touch threshold related to sensitivity */
#define    FT5X0X_REG_THPEAK                 0x81
#define    FT5X0X_REG_THCAL                  0x82
#define    FT5X0X_REG_THWATER                0x83
#define    FT5X0X_REG_THTEMP                 0x84
#define    FT5X0X_REG_THDIFF                 0x85                
#define    FT5X0X_REG_CTRL                   0x86
#define    FT5X0X_REG_TIMEENTERMONITOR       0x87
#define    FT5X0X_REG_PERIODACTIVE           0x88   /* report rate */
#define    FT5X0X_REG_PERIODMONITOR          0x89
#define    FT5X0X_REG_HEIGHT_B               0x8a
#define    FT5X0X_REG_MAX_FRAME              0x8b
#define    FT5X0X_REG_DIST_MOVE              0x8c
#define    FT5X0X_REG_DIST_POINT             0x8d
#define    FT5X0X_REG_FEG_FRAME              0x8e
#define    FT5X0X_REG_SINGLE_CLICK_OFFSET    0x8f
#define    FT5X0X_REG_DOUBLE_CLICK_TIME_MIN  0x90
#define    FT5X0X_REG_SINGLE_CLICK_TIME      0x91
#define    FT5X0X_REG_LEFT_RIGHT_OFFSET      0x92
#define    FT5X0X_REG_UP_DOWN_OFFSET         0x93
#define    FT5X0X_REG_DISTANCE_LEFT_RIGHT    0x94
#define    FT5X0X_REG_DISTANCE_UP_DOWN       0x95
#define    FT5X0X_REG_ZOOM_DIS_SQR           0x96
#define    FT5X0X_REG_RADIAN_VALUE           0x97
#define    FT5X0X_REG_MAX_X_HIGH             0x98
#define    FT5X0X_REG_MAX_X_LOW              0x99
#define    FT5X0X_REG_MAX_Y_HIGH             0x9a
#define    FT5X0X_REG_MAX_Y_LOW              0x9b
#define    FT5X0X_REG_K_X_HIGH               0x9c
#define    FT5X0X_REG_K_X_LOW                0x9d
#define    FT5X0X_REG_K_Y_HIGH               0x9e
#define    FT5X0X_REG_K_Y_LOW                0x9f
#define    FT5X0X_REG_AUTO_CLB_MODE          0xa0
#define    FT5X0X_REG_LIB_VERSION_H          0xa1
#define    FT5X0X_REG_LIB_VERSION_L          0xa2        
#define    FT5X0X_REG_CIPHER                 0xa3
#define    FT5X0X_REG_MODE                   0xa4
#define    FT5X0X_REG_PMODE                  0xa5   /* Power Consume Mode        */    
#define    FT5X0X_REG_FIRMID                 0xa6   /* Firmware version */
#define    FT5X0X_REG_STATE                  0xa7
#define    FT5X0X_REG_FT5201ID               0xa8
#define    FT5X0X_REG_ERR                    0xa9
#define    FT5X0X_REG_CLB                    0xaa



typedef struct R0_LEFT_INPUT_VOLUME_t
{
    uint16_t LINVOL  :6; //Bits 5:0
    uint16_t LIZC    :1; //Bits 6
    uint16_t LINMUTE :1; //Bits 7
    uint16_t IPUV    :1; //Bits 8

} __attribute__((packed, aligned(2))) R0_LEFT_INPUT_VOLUME_t;


typedef struct R1_RIGHT_INPUT_VOLUME_t
{
    uint16_t RINVOL  :6; //Bits 5:0
    uint16_t RIZC    :1; //Bits 6
    uint16_t RINMUTE :1; //Bits 7
    uint16_t IPUV    :1; //Bits 8
    
} __attribute__((packed, aligned(2))) R1_RIGHT_INPUT_VOLUME_t;


typedef struct R2_LOUT1_VOLUME_t
{
    uint16_t LOUT1VOL    :7; //Bits 6:0
    uint16_t LO1ZC       :1; //Bits 7
    uint16_t OUT1VU      :1; //Bits 8
} __attribute__((packed, aligned(2))) R2_LOUT1_VOLUME_t;

typedef struct R3_ROUT1_VOLUME_t
{
    uint16_t ROUT1VOL    :7; //Bits 6:0
    uint16_t RO1ZC       :1; //Bits 7
    uint16_t OUT1VU      :1; //Bits 8
} __attribute__((packed, aligned(2))) R3_ROUT1_VOLUME_t;

typedef struct R4_CLOCKING_1_t{

    uint16_t ADCDIV      :3; //Bits 8:6
    uint16_t DACDIV      :3; //Bits 5:3
    uint16_t SYSCLKDIV   :2; //Bits 2:1
    uint16_t CLKSEL      :1; //Bits 0
} __attribute__((packed, aligned(2))) R4_CLOCKING_1_t;

typedef struct R5_ADC_DAC_CONTROL_CTR1_t{
   
    uint16_t ADCHPD      :1; //Bits 0
    uint16_t DEEMPH      :2; //Bits 2:1
    uint16_t DACMU       :1; //Bits 3
    uint16_t R5RES_4     :1;
    uint16_t ADCPOL      :2; //Bits 6:5
    uint16_t DACDIV2     :1; //Bits 7
    uint16_t R5RES_8     :1;
}__attribute__((packed, aligned(2))) R5_ADC_DAC_CONTROL_CTR1_t ;

typedef struct R6_ADC_DAC_CONTROL_CTR2_t{

    uint16_t DACSLOPE    :1; //Bits 1
    uint16_t DACMR       :1; //Bits 2
    uint16_t DACSMM      :1; //Bits 3
    uint16_t DACPOL      :2; //Bits 6:5
}__attribute__((packed, aligned(2))) R6_ADC_DAC_CONTROL_CTR2_t;

typedef struct R7_AUDIO_INTERFACE_t{
    uint16_t FORMAT       :2; // bit 1:0
    uint16_t WL           :2; // bit 1:0
    uint16_t LRP          :1; // bit 4
    uint16_t DLRSWAP      :1; // bit 5
    uint16_t MS           :1; // bit 6
    uint16_t BCLKINV      :1; // bit 7
    uint16_t ALRSWAP      :1; // bit 8
}__attribute__((packed, aligned(2))) R7_AUDIO_INTERFACE_t;

typedef struct R8_CLOCKING_2_t{
    uint16_t BCLKDIV      :4; // bit 3:0
    uint16_t DCLKDIV      :3; // bit 2:0
}__attribute__((packed, aligned(2))) R8_CLOCKING_2_t;

typedef struct R9_AUDIO_INTERFACE_t{
    uint16_t LOOPBACK     :1; // bit 0
    uint16_t ADCCOMP      :2; // bits 1:0
    uint16_t DACCOMP      :2; // bits 1:0
    uint16_t WL8          :1; // bit 5
    uint16_t ALRCGPIO     :1; // bit 6
}__attribute__((packed, aligned(2))) R9_AUDIO_INTERFACE_t;

typedef struct R10_LEFT_DAC_VOLUME_t{
    uint16_t LDACVOL      :8; // bit 7:0
    uint16_t DACVU        :1; // bit 8
}__attribute__((packed, aligned(2))) R10_LEFT_DAC_VOLUME_t;

typedef struct R11_RIGHT_DAC_VOLUME_t{
    uint16_t RDACVOL      :8; // bit 7:0
    uint16_t DACVU        :1; // bit 8
}__attribute__((packed, aligned(2))) R11_RIGHT_DAC_VOLUME_t;

// typedef struct R15_RESET_t{};

typedef struct R16_3D_CONTROL_t{
    uint16_t D3EN         :1; // bit 0 
    uint16_t D3DEPTH      :4; // bits 3:0
    uint16_t D3LC         :1; // bit 5
    uint16_t D3UC         :1; // bit 6
}__attribute__((packed, aligned(2))) R16_3D_CONTROL_t;

typedef struct R17_ALC1_t{
    uint16_t ALCL         :4; // bits 3:0
    uint16_t MAXGAIN      :3; // bits 2:0
    uint16_t ALCSEL       :2; // bits 1:0
}__attribute__((packed, aligned(2))) R17_ALC1_t;

typedef struct R18_ALC2_t{
    uint16_t HLD          :4; // bits 3:0
    uint16_t MINGAIN      :3; // bits 2:0
}__attribute__((packed, aligned(2))) R18_ALC2_t;

typedef struct R19_ALC3_t{
    uint16_t ATK          :4; // bits 3:0
    uint16_t DCY          :4; // bits 3:0
}__attribute__((packed, aligned(2))) R19_ALC3_t;

typedef struct R20_NOISE_GATE_t{
    uint16_t NGAT         :1; // bit 0
    uint16_t NGTH         :5; // bit 4:0
}__attribute__((packed, aligned(2))) R20_NOISE_GATE_t;

typedef struct R21_LEFT_ADC_VOLUME_t{
    uint16_t LADCVOL      :8; // bits 7:0
    uint16_t ADCVU        :1; // bit  8
}__attribute__((packed, aligned(2))) R21_LEFT_ADC_VOLUME_t;

typedef struct R22_RIGHT_ADC_VOLUME_t{
    uint16_t RADCVOL      :8; // bits 7:0
    uint16_t ADCVU        :1; // bit  8
}__attribute__((packed, aligned(2))) R22_RIGHT_ADC_VOLUME_t;

typedef struct R23_ADDITIONAL_CONTROL_1_t{
    uint16_t TOEN         :1; // bit 1
    uint16_t TOCLKSEL     :1; // bit  2
    uint16_t DATSEL       :2; // bits 1:0
    uint16_t DMONOMIX     :1; // bit 4
    uint16_t VSEL         :2; // bits 1:0
    uint16_t TSDEN        :1; // bit 8
}__attribute__((packed, aligned(2))) R23_ADDITIONAL_CONTROL_1_t;

typedef struct R24_ADDITIONAL_CONTROL_2_t{
    uint16_t LRCM         :1; // bit 2
    uint16_t TRIS         :1; // bit 3
    uint16_t HPSWPOL      :1; // bit 5
    uint16_t HPSWEN       :1; // bit 6
}__attribute__((packed, aligned(2))) R24_ADDITIONAL_CONTROL_2_t;

typedef struct R25_PWR_MGMT_1_t{
    uint16_t DIGENB       :1; // bit 0
    uint16_t MICB         :1; // bit 1
    uint16_t ADCR         :1; // bit 2
    uint16_t ADCL         :1; // bit 3
    uint16_t AINR         :1; // bit 4
    uint16_t AINL         :1; // bit 5
    uint16_t VREF         :1; // bit 6
    uint16_t VMIDSEL      :2; // bit 1:0
}__attribute__((packed, aligned(2))) R25_PWR_MGMT_1_t;

typedef struct R26_PWR_MGMT_2_t{
    uint16_t PLL_EN       :1; // bit 0
    uint16_t OUT3         :1; // bit 1
    uint16_t SPKR         :1; // bit 3
    uint16_t SPKL         :1; // bit 4
    uint16_t ROUT1        :1; // bit 5
    uint16_t LOUT1        :1; // bit 6
    uint16_t DACR         :1; // bit 7
    uint16_t DACL         :1; // bit 8
}__attribute__((packed, aligned(2))) R26_PWR_MGMT_2_t;

typedef struct R27_ADDITIONAL_CONTROL_3_t{
    uint16_t ADC_ALC_SR   :3; // bits 2:0
    uint16_t OUT3CAP      :1; // bit 3
    uint16_t VROI         :1; // bit 6
}__attribute__((packed, aligned(2))) R27_ADDITIONAL_CONTROL_3_t;

typedef struct R28_ANTI_POP_1_t{
    uint16_t HPSTBY       :1; // bit 0
    uint16_t SOFT_ST      :1; // bit 2
    uint16_t BUFIOEN      :1; // bit 3
    uint16_t BUFDCOPEN    :1; // bit 4
    uint16_t POBCTRL      :1; // bit 7
}__attribute__((packed, aligned(2))) R28_ANTI_POP_1_t;

typedef struct R29_ANTI_POP_2_t{
    uint16_t DRES         :2; // bits 1:0
    uint16_t DISOP        :1; // bit 5
}__attribute__((packed, aligned(2))) R29_ANTI_POP_2_t;

typedef struct R32_ADCL_SIGNAL_PATH_t{
    uint16_t LMIC2B       :1; // bit 3
    uint16_t LMICBOOST    :2; // bits 1:0
    uint16_t LMP2         :1; // bit 6
    uint16_t LMP3         :1; // bit 7
    uint16_t LMN1         :1; // bit 8
}__attribute__((packed, aligned(2))) R32_ADCL_SIGNAL_PATH_t;

typedef struct R33_ADCR_SIGNAL_PATH_t{
    uint16_t RMIC2B       :1; // bit 3
    uint16_t RMICBOOST    :2; // bits 1:0
    uint16_t RMP2         :1; // bit 6
    uint16_t RMP3         :1; // bit 7
    uint16_t RMN1         :1; // bit 8
}__attribute__((packed, aligned(2))) R33_ADCR_SIGNAL_PATH_t;

typedef struct R34_LEFT_OUT_MIX_1_t{
    uint16_t LI2LOVOL     :3; // bits 2:0
    uint16_t LI2LO        :1; // bit 7
    uint16_t LD2LO        :1; // bit 8
}__attribute__((packed, aligned(2))) R34_LEFT_OUT_MIX_1_t;

typedef struct R37_RIGHT_OUT_MIX_2_t{
    uint16_t RI2ROVOL     :3; // bits 2:0
    uint16_t RI2RO        :1; // bit 7
    uint16_t RD2RO        :1; // bit 8
}__attribute__((packed, aligned(2))) R37_RIGHT_OUT_MIX_2_t;

typedef struct R38_MONO_OUT_MIX_1_t{
    uint16_t L2MO         :1; // bit 7
}__attribute__((packed, aligned(2))) R38_MONO_OUT_MIX_1_t;

typedef struct R39_MONO_OUT_MIX_2_t{
    uint16_t R2MO         :1; // bit 7
}__attribute__((packed, aligned(2))) R39_MONO_OUT_MIX_2_t;

typedef struct R40_LOUT2_VOLUME_t{
    uint16_t SPKLVOL      :7; // bits 6:0
    uint16_t SPKLZC       :1; // bit 7
    uint16_t SPKVU        :1; // bit 8
}__attribute__((packed, aligned(2))) R40_LOUT2_VOLUME_t;

typedef struct R41_ROUT2_VOLUME_t{
    uint16_t SPKRVOL      :7; // bits 6:0
    uint16_t SPKLZC       :1; // bit 7
    uint16_t SPKVU        :1; // bit 8
}__attribute__((packed, aligned(2))) R41_ROUT2_VOLUME_t;

typedef struct R42_MONOOUT_VOLUME_t{
    uint16_t MOUTVOL      :1; //bit 6
}__attribute__((packed, aligned(2))) R42_MONOOUT_VOLUME_t;

typedef struct R43_INPUT_BOOST_MIXER_1_t{
    uint16_t LIN2BOOST    :3; // bits 2:0
    uint16_t LIN3BOOST    :3; // bits 2:0
}__attribute__((packed, aligned(2))) R43_INPUT_BOOST_MIXER_1_t;

typedef struct R44_INPUT_BOOST_MIXER_2_t{
    uint16_t RIN2BOOST    :3; // bits 2:0
    uint16_t RIN3BOOST    :3; // bits 2:0
}__attribute__((packed, aligned(2))) R44_INPUT_BOOST_MIXER_2_t;

typedef struct R45_BYPASS_1_t{
    uint16_t LB2LOVOL     :3; // bits 2:0
    uint16_t LB2LO        :1; // bit 5
}__attribute__((packed, aligned(2))) R45_BYPASS_1_t;

typedef struct R46_BYPASS_2_t{
    uint16_t RB2ROVOL     :3; // bits 2:0
    uint16_t RB2RO        :1; // bit 5
}__attribute__((packed, aligned(2))) R46_BYPASS_2_t;

typedef struct R47_PWR_MGMT_3_t{
    uint16_t ROMIX        :1; // bit 2
    uint16_t LOMIX        :1; // bit 3
    uint16_t RMIC         :1; // bit 4
    uint16_t LMIC         :1; // bit 5
}__attribute__((packed, aligned(2))) R47_PWR_MGMT_3_t;

typedef struct R48_ADDITIONAL_CONTROL_4_t{
    uint16_t MBSEL        :1; // bit 0
    uint16_t TSENSEN      :1; // bit 1
    uint16_t HPSEL        :2; // bits 1:0
    uint16_t GPIOSEL      :3; // bits 2:0
    uint16_t GPIOPOL      :1; // bit 7
}__attribute__((packed, aligned(2))) R48_ADDITIONAL_CONTROL_4_t;

typedef struct R49_CLASS_D_CONTROL_1_t{
    uint16_t SPK_OP_EN    :2; // bits 1:0
}__attribute__((packed, aligned(2))) R49_CLASS_D_CONTROL_1_t;

typedef struct R51_CLASS_D_CONTROL_3_t{
    uint16_t ACGAIN       :3; // bits 2:0
    uint16_t DCGAIN       :3; // bits 2:0
}__attribute__((packed, aligned(2))) R51_CLASS_D_CONTROL_3_t;

typedef struct R52_PLL_N_t{
    uint16_t PLLN         :4; // bits 3:0
    uint16_t PLLRESCALE   :1; // bit 4
    uint16_t SDM          :1; // bit 5
    uint16_t OPCLKDIV     :3; // bits 2:0
}__attribute__((packed, aligned(2))) R52_PLL_N_t;

typedef struct R53_PLL_K_1_t{
    uint16_t PLLK         :8; // bits 23:16 
}__attribute__((packed, aligned(2))) R53_PLL_K_1_t;

typedef struct R54_PLL_K_2_t{
    uint16_t PLLK         :8; // bits 15:8 
}__attribute__((packed, aligned(2))) R54_PLL_K_2_t;

typedef struct R55_PLL_K_3_t{
    uint16_t PLLK         :8; // bits 7:0 
}__attribute__((packed, aligned(2))) R55_PLL_K_3_t;



#endif 