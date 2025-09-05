#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/i2c_master.h"
// #include "driver/i2c_slave.h"

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
    #if CONFIG_USE_I2C_UTILS
        i2c_scanner_config_t config = I2C_SCANNER_DEFAULT_CONFIG();

        esp_err_t ret = i2c_scanner_init(&config);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to initialize I2C scanner: %s", esp_err_to_name(ret));
            return;
        }

        i2c_scanner_print_results(I2C_NUM_0);
    #else
        ESP_LOGW(TAG, "I2C utils is disabled in menuconfig");
    #endif
}