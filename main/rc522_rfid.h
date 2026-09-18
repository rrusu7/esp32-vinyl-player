#ifndef RC522_RFID_H
#define RC522_RFID_H

#include "rc522.h"
#include "driver/rc522_spi.h"

static const char* TAG = "RC522-logic";

#define RC522_SPI_BUS_GPIO_MISO    (19)
#define RC522_SPI_BUS_GPIO_MOSI    (23)
#define RC522_SPI_BUS_GPIO_SCLK    (18)
#define RC522_SPI_SCANNER_GPIO_SDA (5)
#define RC522_SCANNER_GPIO_RST     (GPIO_NUM_21)

extern spi_bus_config_t bus_config;
extern rc522_spi_config_t driver_config;
extern rc522_driver_handle_t driver;
extern rc522_handle_t scanner;

void init_bus_config();
void init_driver_config();
void picc_state_changed(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void spi_driver_config();
void scanner_config();

#endif // RC522_RFID_H