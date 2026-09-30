#ifndef RC522_RFID_H
#define RC522_RFID_H

#include "rc522.h"
#include "driver/rc522_spi.h"

extern spi_bus_config_t bus_config;
extern rc522_spi_config_t driver_config;
extern rc522_driver_handle_t driver;
extern rc522_handle_t scanner;

//Main does not need to know about the internal functions of rc522_rfid.cpp, so we only expose the scanner_config function to main.cpp. The other functions are used internally in rc522_rfid.cpp to configure the driver and scanner.
// void init_bus_config();
// void init_driver_config();
// void picc_state_changed(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
// void spi_driver_config();
// void scanner_config();
void init_rc522();

#endif // RC522_RFID_H