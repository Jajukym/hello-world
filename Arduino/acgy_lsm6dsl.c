/**
 * @file ac_gy_lsm6dsl.c
 *
 * @author spencer jackson
 * @date Initial: 19 Mar 2018
 * @version 1
 * @date Released: 19 Mar 2018
 * @brief driver for lsm6dsl accel/gyro IC
 * @detail this file is focused strictly on retrieving the data, not the processing, it implements the accel_gyro feature header.
 */

#include"ML.h"
#include"features/accel_gyro.h"
#include"drivers/ML_spi.h"
#include"drivers/ML_gpio.h"
#include"FreeRTOS.h"
#include"timers.h"

#define ACCEL_FULLSCALE 8
#define GYRO_FULLSCALE 500

#define SPI_READ_BIT            0x80
#define SPI_WRITE_BIT           0x00

// Selected Accelerometer Register Definitions
#define FUNC_CFG_ACCESS 0x01
#define SENSOR_SYNC_TIME_FRAME 0x04
#define SENSOR_SYNC_RES_RATIO 0x05
#define FIFO_CTRL1 0x06
#define FIFO_CTRL2 0x07
#define FIFO_CTRL3 0x08
#define FIFO_CTRL4 0x09
#define FIFO_CTRL5 0x0A
#define DRDY_PULSE_CFG_G 0x0B
#define INT1_CTRL 0x0D
#define INT2_CTRL 0x0E
#define WHO_AM_I 0x0F
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define CTRL3_C 0x12
#define CTRL4_C 0x13
#define CTRL5_C 0x14
#define CTRL6_C 0x15
#define CTRL7_G 0x16
#define CTRL8_XL 0x17
#define CTRL9_XL 0x18
#define CTRL10_C 0x19
#define MASTER_CONFIG 0x1A
#define WAKE_UP_SRC 0x1B
#define TAP_SRC 0x1C
#define D6D_SRC 0x1D
#define STATUS_REG 0x1E
#define OUT_TEMP_L 0x20
#define OUT_TEMP_H 0x21
#define OUTX_L_G 0x22
#define OUTX_H_G 0x23
#define OUTY_L_G 0x24
#define OUTY_H_G 0x25
#define OUTZ_L_G 0x26
#define OUTZ_H_G 0x27
#define OUTX_L_XL 0x28
#define OUTX_H_XL 0x29
#define OUTY_L_XL 0x2A
#define OUTY_H_XL 0x2B
#define OUTZ_L_XL 0x2C
#define OUTZ_H_XL 0x2D
#define SENSORHUB1_REG 0x2E
#define SENSORHUB2_REG 0x2F
#define SENSORHUB3_REG 0x30
#define SENSORHUB4_REG 0x31
#define SENSORHUB5_REG 0x32
#define SENSORHUB6_REG 0x33
#define SENSORHUB7_REG 0x34
#define SENSORHUB8_REG 0x35
#define SENSORHUB9_REG 0x36
#define SENSORHUB10_REG 0x37
#define SENSORHUB11_REG 0x38
#define SENSORHUB12_REG 0x39
#define FIFO_STATUS1 0x3A
#define FIFO_STATUS2 0x3B
#define FIFO_STATUS3 0x3C
#define FIFO_STATUS4 0x3D
#define FIFO_DATA_OUT_L 0x3E
#define FIFO_DATA_OUT_H 0x3F
#define TIMESTAMP0_REG 0x40
#define TIMESTAMP1_REG 0x41
#define TIMESTAMP2_REG 0x42
#define STEP_TIMESTAMP_L 0x49
#define STEP_TIMESTAMP_H 0x4A
#define STEP_COUNTER_L 0x4B
#define STEP_COUNTER_H 0x4C
#define SENSORHUB13_REG 0x4D
#define SENSORHUB14_REG 0x4E
#define SENSORHUB15_REG 0x4F
#define SENSORHUB16_REG 0x50
#define SENSORHUB17_REG 0x51
#define SENSORHUB18_REG 0x52
#define FUNC_SRC1 0x53
#define FUNC_SRC2 0x54
#define WRIST_TILT_IA 0x55
#define TAP_CFG 0x58
#define TAP_THS_6D 0x59
#define INT_DUR2 0x5A
#define WAKE_UP_THS 0x5B
#define WAKE_UP_DUR 0x5C
#define FREE_FALL 0x5D
#define MD1_CFG 0x5E
#define MD2_CFG 0x5F
#define MASTER_CMD_CODE 0x60
#define SENS_SYNC_SPI_ERROR_CODE 0x61
#define OUT_MAG_RAW_X_L 0x66
#define OUT_MAG_RAW_X_H 0x67
#define OUT_MAG_RAW_Y_L 0x68
#define OUT_MAG_RAW_Y_H 0x69
#define OUT_MAG_RAW_Z_L 0x6A
#define OUT_MAG_RAW_Z_H 0x6B
#define X_OFS_USR 0x73
#define Y_OFS_USR 0x74
#define Z_OFS_USR 0x75

#define XLDA 0x01
#define GDA 0x02

typedef enum lsm_state_t
{
    UNINIT = 0,
    RESET,
    RESET_1,
    RESET_2,
    WAIT,
    SETUP,
    SETUP_1,
    //SETUP_2,
    RUN
} lsm_state_t;


static ml_sched_cb_f the_cb;
static TimerHandle_t the_timer;
static lsm_state_t   the_state;

void lsm_state_next(uint16_t size, void *data);

//query for latest data
void lsm_ask()
{
    uint8_t buf[] = {OUTX_L_G | SPI_READ_BIT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(the_state != RUN)
    {
        ml_sched_add(lsm_state_next, 0, 0);
        return;
    }
    ml_spi_write(ACCEL_SPI_ID, buf, 1, 12); //write 1 read 12 (after the write)
}

//reset accel
void lsm_reset(void)
{
    //  Reset flow is as follows:
    //  1. Set the Gyroscope in Power-Down mode;
    //  2. Set the Accelerometer in High-Performance mode;
    //  3. Set to 1 the SW_RESET bit of the CTRL3_C register;
    //  4. Wait 50 μs (or wait until the SW_RESET bit of the CTRL3_C register returns to 0).

    //TODO: these assume blocking calls
    uint8_t buf[3];

    switch(the_state)
    {
    default:
        the_state = RESET;//start over
    case RESET:
        buf[0] = CTRL2_G | SPI_WRITE_BIT;
        buf[1] = 0x00;  //ODR_G = 4, FS_G = 1, FS_125 = 0
        break;

    case RESET_1:
        buf[0] = CTRL6_C | SPI_WRITE_BIT;
        buf[1] = 0x00;  //TRIG_EN = 0, LVLen = 0, LVL2_EN = 0, XL_HM_MODE = 0
        break;

    case RESET_2:
        buf[0] = CTRL3_C | SPI_WRITE_BIT;
        buf[1] = 0x01;  //BOOT = 0, BDU = 0, H_LACTIVE = 0, PP_OD = 0, SIM = 0, IF_INC = 0, BLE = 0, SW_RESET = 1
        break;
    }
    ml_spi_write(ACCEL_SPI_ID, buf, 2, 0); //write 2 read 0

    //now wait
    xTimerStart(the_timer, 1);
}

//configure accel
void lsm_setup(void)
{
    uint8_t buf[12];
    if(the_state < SETUP)
    {
        lsm_reset();
        return;
    }

    switch(the_state)
    {
    case SETUP:
        // note that the array index aligns with the ctrl reg number
        buf[0] = CTRL1_XL | SPI_WRITE_BIT;  // ACCEL_ODR
#if ACCEL_FULLSCALE  == 8
        buf[1] = 0x4C;  //ODR_XL = 4, FS_XL = 3 (8g), LPF1_BW_SEL = 0, BW_XL = 0
#else
#error("accel full scale not properly configured")
#endif //ACCEL_FULLSCALE
#if GYRO_FULLSCALE ==  500
        buf[2] = 0x44;  //ODR_G = 4, FS_G = 1 (500dps), FS_125 = 0
#else
#error("gyro full scale not properly configured")
#endif //GYRO_FULLSCALE
        buf[3] = 0x04;  //BOOT = 0, BDU = 0, H_LACTIVE = 0, PP_OD = 0, SIM = 0, IF_INC = 1, BLE = 0, SW_RESET = 0
        buf[4] = 0x04;  //DEN_XL_EN = 0, SLEEP_G = 0, DEN_DRDY_INT1 = 0, INT2_on_INT1 = 0, DRDY_MASK = 0, I2C_disable = 1, STOP_ON_FTH = 0
        buf[5] = 0x00;  //ROUNDING = 0, DEN_LH = 0, ST_G = 0, ST_XL = 0
        buf[6] = 0x18;  //TRIG_EN = 0, LVLen = 0, LVL2_EN = 0, XL_HM_MODE = 1, USR_OFF_W = 1, FTYPE[1:0] = 0
        buf[7] = 0x80;  //G_HM_MODE = 1, HP_G_EN = 0, HPM_G[1:0] = 0, ROUNDING_STATUS = 0
        buf[8] = 0x00;  //LPF2_XL_EN = 0, HPCF_XL[1:0] = 0, HP_REF_MODE = 0, INPUT_COMPOSITE = 0, HP_SLOPE_XL_EN = 0, LOW_PASS_ON_6D = 0
        buf[9] = 0x00;  //Zen_XL = 1, Yen_XL = 1, Xen_XL = 1, SOFT_EN = 0
        buf[10] = 0x00; //Zen_G = 1, Yen_G = 1, Xen_G = 1, FUNC_EN = 0, PEDO_RST_STEP = 0, SIGN_MOTION_EN = 0
        ml_spi_write(ACCEL_SPI_ID, buf, 11, 0); //write 11 read 0
        break;

    case SETUP_1:
#if(0)
        // note that the array index aligns with the ctrl reg number
        buf[0] = FIFO_CTRL1 | SPI_WRITE_BIT;
        buf[1] = 0x96;  //set the fifo threshold to something reasonable
        buf[2] = 0x00;
        buf[3] = 0x09;  //no fifo use
        buf[4] = 0x00;
        buf[5] = 0x46;  //continuous mode
        ml_spi_write(ACCEL_SPI_ID, buf, 6, 0); //write 6 read 0
        break;

    case SETUP_2:
#endif //0
        buf[0] = INT1_CTRL | SPI_WRITE_BIT;
        buf[1] = 0x01; //set pin when data ready
        ml_spi_write(ACCEL_SPI_ID, buf, 2, 0); //write 2 read 0
        break;

#if(0)
    case SETUP_3:
        if(calibration_storage_set)
        {

            spi_details.tx_buffer_size = 4;
            spi_details.rx_buffer_size = 0;
            buf[0] = X_OFS_USR | SPI_WRITE_BIT;
            buf[1] = calibration_storage.x_cal_data;
            buf[2] = calibration_storage.y_cal_data;
            buf[3] = calibration_storage.z_cal_data;
            ml_spi_write(ACCEL_SPI_ID, buf, 4, 0); //write 4 read 0
        }
        break;
#endif //0

    default:
        return;
    }

    //now wait
    //xTimerStart(the_timer, 1);
}

//executes on fifo after timer trips
void lsm_state_next(uint16_t size, void *data)
{
    (void)size;
    (void)data;
    if(the_state < RUN)
    {
        the_state++;
    }
    if(the_state == WAIT)
    {
        xTimerStart(the_timer, 1);
    }
    else if(the_state < SETUP)
    {
        lsm_reset();
    }
    else if(the_state < RUN)
    {
        lsm_setup();
    }
    else
    {
        //ask the first time to get the ball rolling
        lsm_ask();
    }
}

//timer callback
void lsm_state_timer(TimerHandle_t tim)
{
    (void) tim;
    ml_sched_add(lsm_state_next, 0, 0);
}

//callback lets us know transmission is complete
void lsm_cb(uint16_t size, void *data)
{
    uint8_t *d = (uint8_t *)data;
    int16_t tmp;
    float conv;
    accel_gyro_data_s measured;
    //TODO: make sure size is appropriate

    if(the_state < RUN)
    {
        //just continue the state machine
        ml_sched_add(lsm_state_next, 0, 0);
        return;
    }

    //process the spi part
    //first gyros
    conv = .01745329*(float)GYRO_FULLSCALE/32767.0;//convert to rad/sec
    conv = (float)GYRO_FULLSCALE/32767.0;//convert to rad/sec 
    tmp = d[0] + ((int16_t)d[1] << 8);
    measured.pitch = (float)tmp*conv;
    tmp = d[2] + ((int16_t)d[3] << 8);
    measured.roll = (float)tmp*conv;
    tmp = d[4] + ((int16_t)d[5] << 8);
    measured.yaw  = (float)tmp*conv;
    
    //now accels
    conv = 9.80665*(float)ACCEL_FULLSCALE/32767.0;//convert to m/sec^2
    conv = (float)ACCEL_FULLSCALE/32767.0;//convert to m/sec^2
    tmp = d[6] + ((int16_t)d[7] << 8);
    measured.x = (float)tmp*conv;
    tmp = d[8] + ((int16_t)d[9] << 8);
    measured.y = (float)tmp*conv;
    tmp = d[10] + ((int16_t)d[11] << 8);
    measured.z = (float)tmp*conv;

    //now call the callback:
    the_cb(sizeof(measured), &measured);
    //we will ask again when data is ready (via INT1 pin)
}

void lsm_data_ready_cb(uint16_t size, void *data)
{
    (void)size;
    (void)data;
    lsm_ask();
}

//this is the public API
bool accel_gyro_init(ml_sched_cb_f cb)
{
    ml_spi_init(ACCEL_SPI_ID, lsm_cb);
    the_cb = cb;

    the_timer = xTimerCreate("SPI delay",
                             pdMS_TO_TICKS(200),
                             pdFALSE,//autoreset
                             (void *)0, //id
                             lsm_state_timer
                            );

    ml_gpio_pin_init(ACCEL_INT_PIN_ID, lsm_data_ready_cb);

    lsm_reset();
    return true;
}
