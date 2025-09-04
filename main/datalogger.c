#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"

#if CONFIG_USE_I2C_UTILS
    #include "i2c_utils.h"
#endif

#if CONFIG_USE_BH1750
    #include "i2c_utils.h"
#endif

#if CONFIG_USE_BH1750
    #include "i2c_utils.h"
#endif

static const char *TAG = "ESP32_DATALOGGER";

void app_main(void)
{

    i2c_scanner_config_t config = I2C_SCANNER_DEFAULT_CONFIG();
    i2c_scanner_init(&config);

    i2c_scanner_print_results(I2C_NUM_0);

}