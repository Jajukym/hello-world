#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "nrf51_bitfields.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "boards.h"
#include "softdevice_handler.h"
#include "app_timer.h"
#include "app_trace.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "bsp_btn_ble.h"
#include "app_uart.h"
#include "custom_peripheral_service.h"
#include "FreeRTOS.h"
#include "task.h"

#define DEVICE_NAME                      "Custom_BLE_w/_RTOS"                       /**< Name of device. Will be included in the advertising data. */
#define APP_ADV_INTERVAL                 300                                        /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS       0                                          /**< The advertising timeout in units of seconds. */

#define MIN_CONN_INTERVAL                MSEC_TO_UNITS(100, UNIT_1_25_MS)           /**< Minimum acceptable connection interval (0.1 seconds). */
#define MAX_CONN_INTERVAL                MSEC_TO_UNITS(500, UNIT_1_25_MS)           /**< Maximum acceptable connection interval (0.5 second). */
#define SLAVE_LATENCY                    0                                          /**< Slave latency. */
#define CONN_SUP_TIMEOUT                 MSEC_TO_UNITS(4000, UNIT_10_MS)            /**< Connection supervisory timeout (4 seconds). */


static uint16_t                          m_conn_handle = BLE_CONN_HANDLE_INVALID;   /**< Handle of the current connection. */
static ble_uuid_t m_adv_uuids[] = {{BLE_UUID_CUSTOM_SERVICE,         BLE_UUID_TYPE_BLE}}; /**< Universally unique service identifiers. */ 
uint8_t char2_data[CHARACTERISTIC_SIZE];

#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 1                           /**< UART RX buffer size. */

/*debug functions*/
#ifdef DEBUG
#define DEBUG_PRINT 1
#else
#define DEBUG_PRINT 0
#endif
#define DEBUG_PRINTF(...) do{ if (DEBUG_PRINT) {printf(__VA_ARGS__); printf("\r\n"); }} while(0)

/*functions*/
static void uart_error_handle(app_uart_evt_t * p_event);
static void ble_stack_init(void);
static void device_manager_init(bool erase_bonds);
static void gap_params_init(void);
static void advertising_init(void);
static void services_init(void);

/* RTOS parameters */
#define BLE_TASK_PRIORITY           ( tskIDLE_PRIORITY + 2 )
#define BLINKY_TASK_PRIORITY        ( tskIDLE_PRIORITY + 1 )
static void task_blinky(void *pvParameters);
static void task_ble_process(void *pvParameters);

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    uint32_t err_code;

    const app_uart_comm_params_t comm_params =
      {
          RX_PIN_NUMBER,
          TX_PIN_NUMBER,
          RTS_PIN_NUMBER,
          CTS_PIN_NUMBER,
          APP_UART_FLOW_CONTROL_ENABLED,
          false,
          UART_BAUDRATE_BAUDRATE_Baud115200
      };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOW,
                         err_code);
    APP_ERROR_CHECK(err_code);

    DEBUG_PRINTF("");
    DEBUG_PRINTF("=============");
    DEBUG_PRINTF("Device booted");
    DEBUG_PRINTF("=============");
    ble_stack_init();
    gap_params_init();
    advertising_init();
    services_init();

    // Start execution.
    err_code = ble_advertising_start(BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(err_code);
    /* Configure LED-pins as outputs */
    nrf_gpio_cfg_output(LED_RGB_GREEN);
    nrf_gpio_cfg_output(LED_RGB_BLUE);
    /* tasks */
    xTaskCreate(task_ble_process,"BLE Task",configMINIMAL_STACK_SIZE,NULL,BLE_TASK_PRIORITY,NULL);
    xTaskCreate(task_blinky,"Blinky Task",configMINIMAL_STACK_SIZE,NULL,BLINKY_TASK_PRIORITY,NULL);
    vTaskStartScheduler();
    /*don't actually get here*/
    while(1);
}

static void task_ble_process( void *pvParameters )
{
    uint8_t i=0;
    uint32_t err_code;
    while(1)
    {
        nrf_gpio_pin_toggle(LED_RGB_GREEN);
        vTaskDelay(500);
        for(i=0;i<CHARACTERISTIC_SIZE;i++)
        {
            char2_data[i] = char2_data[i]+1;
        }
        err_code = custom_service_update_data(m_conn_handle,char2_data);
        APP_ERROR_CHECK(err_code);
    }
}

static void task_blinky( void *pvParameters )
{
    while(1)
    {
        nrf_gpio_pin_toggle(LED_RGB_BLUE);
        vTaskDelay(100);
    }
}

void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name){
    DEBUG_PRINTF("app_error_handler\r\nerror_code=%u\r\nline_num=%u\r\nfile_name=%s",error_code,line_num,p_file_name);
}

void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num   Line number of the failing ASSERT call.
 * @param[in] file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(1, line_num, p_file_name);
}


/**@brief Function for the GAP initialization.
 *
 * @details This function sets up all the necessary GAP (Generic Access Profile) parameters of the
 *          device including the device name, appearance, and the preferred connection parameters.
 */
static void gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;

    DEBUG_PRINTF("gap_params_init");
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
}

static void services_init(void)
{
    uint32_t       err_code;
    err_code = custom_service_init();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
    switch (ble_adv_evt)
    {
        case BLE_ADV_EVT_FAST:
            DEBUG_PRINTF("BLE_ADV_EVT_FAST");
            break;
        case BLE_ADV_EVT_IDLE:
            DEBUG_PRINTF("BLE_ADV_EVT_IDLE");
            break;
        default:
            break;
    }
}


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint8_t i=0;
    switch (p_ble_evt->header.evt_id)
            {
        case BLE_GAP_EVT_CONNECTED:
            DEBUG_PRINTF("BLE_GAP_EVT_CONNECTED");
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            break;
        case BLE_GAP_EVT_DISCONNECTED:
            DEBUG_PRINTF("BLE_GAP_EVT_DISCONNECTED");
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
            break;
        case BLE_GAP_EVT_TIMEOUT:
            DEBUG_PRINTF("BLE_GAP_EVT_TIMEOUT");
        case BLE_GATTS_EVT_WRITE:
            DEBUG_PRINTF("BLE_GATTS_EVT_WRITE");
            for(i=0;i<p_ble_evt->evt.gatts_evt.params.write.len;i++) DEBUG_PRINTF("Data %d: 0x%x",i,p_ble_evt->evt.gatts_evt.params.write.data[i]);
        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the BLE Stack event interrupt handler after a BLE stack
 *          event has been received.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    ble_conn_params_on_ble_evt(p_ble_evt);
    on_ble_evt(p_ble_evt);
    ble_advertising_on_ble_evt(p_ble_evt);
}


/**@brief Function for dispatching a system event to interested modules.
 *
 * @details This function is called from the System event interrupt handler after a system
 *          event has been received.
 *
 * @param[in] sys_evt  System stack event.
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
    ble_advertising_on_sys_evt(sys_evt);
}


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    uint32_t err_code;

    DEBUG_PRINTF("ble_stack_init");
    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, NULL);    
    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));
    ble_enable_params.gatts_enable_params.service_changed = 1;
    err_code = sd_ble_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the Advertising functionality.
 */
static void advertising_init(void)
{
    uint32_t      err_code;
    ble_advdata_t advdata;

    DEBUG_PRINTF("advertising_init");
    // Build advertising data struct to pass into @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = true;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = m_adv_uuids;

    ble_adv_modes_config_t options = {0};
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    options.ble_adv_fast_timeout  = APP_ADV_TIMEOUT_IN_SECONDS;

    err_code = ble_advertising_init(&advdata, NULL, &options, on_adv_evt, NULL);
    APP_ERROR_CHECK(err_code);
}