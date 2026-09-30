#include "spi_bus_config.h"
#include "micro_sd.h"
#include "rc522_rfid.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(){

  init_bus_config();      //Initialize the SPI bus for the RC522 scanner
  init_sd_card();       //Initialize the SD card and mount the filesystem
  init_rc522();       //Initialize the RC522 scanner and start it

  while(true){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}