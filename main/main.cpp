#include "rc522_rfid.h" 

extern "C" void app_main(){

  init_bus_config();  //Configure the SPI bus parameters
  init_driver_config(); //Configure the RC522 driver parameters
  spi_driver_config();  //Initialize the SPI driver and install it
  scanner_config(); //Create the RC522 scanner instance and configure it
  rc522_start(scanner); //Start the RC522 scanner

  while(true){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}