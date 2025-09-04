#include "i2c_utils.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static const char *TAG = "I2C_UTILS";

esp_err_t i2c_scanner_init(const i2c_scanner_config_t *config)
{
    if (config == NULL) {
        ESP_LOGE(TAG, "Configuration is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = config->sda_pin,
        .scl_io_num = config->scl_pin,
        .sda_pullup_en = config->sda_pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .scl_pullup_en = config->scl_pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .master.clk_speed = config->clk_speed,
        .clk_flags = 0,
    };

    esp_err_t ret = i2c_param_config(config->port, &i2c_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure I2C parameters: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = i2c_driver_install(config->port, I2C_MODE_MASTER, 0, 0, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install I2C driver: %s", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "I2C scanner initialized on port %d", config->port);
    return ESP_OK;
}

esp_err_t i2c_scanner_deinit(i2c_port_t port)
{
    esp_err_t ret = i2c_driver_delete(port);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to delete I2C driver: %s", esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "I2C scanner deinitialized on port %d", port);
    return ESP_OK;
}

bool i2c_scanner_device_exists(i2c_port_t port, uint8_t address)
{
    if (address == 0 || address > 126) {
        return false;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if (cmd == NULL) {
        return false;
    }

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    return (ret == ESP_OK);
}

int i2c_scanner_scan(i2c_port_t port, uint8_t *found_devices, size_t max_devices)
{
    int device_count = 0;
    
    ESP_LOGI(TAG, "Scanning I2C bus on port %d...", port);
    
    for (int addr = 1; addr <= 126; addr++) {
        if (i2c_scanner_device_exists(port, addr)) {
            ESP_LOGI(TAG, "Found device at address 0x%02x", addr);
            
            // Store address if array is provided and there's space
            if (found_devices != NULL && device_count < max_devices) {
                found_devices[device_count] = addr;
            }
            device_count++;
        }
    }
    
    ESP_LOGI(TAG, "I2C scan completed. Found %d devices", device_count);
    return device_count;
}

void i2c_scanner_print_results(i2c_port_t port)
{
    printf("Scanning I2C Bus on port %d........\n", port);
    
    int device_count = 0;
    for (int addr = 1; addr <= 126; addr++) {
        if (i2c_scanner_device_exists(port, addr)) {
            printf("Found device at address 0x%02x\n", addr);
            device_count++;
        }
    }
    
    printf("I2C scan completed. Found %d devices\n", device_count);
}