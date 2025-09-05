/**
 * @file i2c_utils.h
 * @brief I2C Utilities 
 */

#ifndef I2C_UTILS_H
#define I2C_UTILS_H

#include "driver/i2c.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief I2C Scanner configuration structure
 */
typedef struct {
    i2c_port_t port;        ///< I2C port number (I2C_NUM_0 or I2C_NUM_1)
    gpio_num_t sda_pin;     ///< SDA pin number
    gpio_num_t scl_pin;     ///< SCL pin number
    uint32_t clk_speed;     ///< I2C clock speed in Hz
    bool sda_pullup;        ///< Enable SDA pullup resistor
    bool scl_pullup;        ///< Enable SCL pullup resistor
} i2c_scanner_config_t;

/**
 * @brief Default I2C scanner configuration
 */
#define I2C_SCANNER_DEFAULT_CONFIG() {          \
    .port = I2C_NUM_0,                          \
    .sda_pin = GPIO_NUM_21,                     \
    .scl_pin = GPIO_NUM_22,                     \
    .clk_speed = 100000,                        \
    .sda_pullup = true,                         \
    .scl_pullup = true                          \
}

/**
 * @brief Initialize I2C scanner
 * 
 * @param config Pointer to I2C scanner configuration
 * 
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t i2c_scanner_init(const i2c_scanner_config_t *config);

/**
 * @brief Deinitialize I2C scanner
 * 
 * @param port I2C port number
 * 
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t i2c_scanner_deinit(i2c_port_t port);

/**
 * @brief Scan I2C bus for devices
 * 
 * @param port I2C port number
 * @param found_devices Array to store found device addresses (optional, can be NULL)
 * @param max_devices Maximum number of devices to store in found_devices array
 * 
 * @return Number of devices found, or negative error code
 */
int i2c_scanner_scan(i2c_port_t port, uint8_t *found_devices, size_t max_devices);

/**
 * @brief Check if a specific I2C device exists
 * 
 * @param port I2C port number
 * @param address Device address (7-bit)
 * 
 * @return true if device exists, false otherwise
 */
bool i2c_scanner_device_exists(i2c_port_t port, uint8_t address);

/**
 * @brief Print scan results to console
 * 
 * @param port I2C port number
 */
void i2c_scanner_print_results(i2c_port_t port);

#ifdef __cplusplus
}
#endif

#endif /* I2C_UTILS_H */ 