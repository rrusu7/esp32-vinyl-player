#include "rc522_rfid.h"
#include "driver/sdspi_host.h"

#define SD_SPI_CS_GPIO GPIO_NUM_4

static sdspi_device_config_t sdspi_config = SDSPI_DEVICE_CONFIG_DEFAULT();

static sdspi_dev_handle_t out_handle;

extern "C" void app_main(){

  init_bus_config();  //Configure the SPI bus parameters
  init_driver_config(); //Configure the RC522 driver parameters
  spi_driver_config();  //Initialize the SPI driver and install it
  scanner_config(); //Create the RC522 scanner instance and configure it
  rc522_start(scanner); //Start the RC522 scanner

  sdspi_config.host_id = SPI3_HOST;
  sdspi_config.gpio_cs = SD_SPI_CS_GPIO;

  sdspi_host_init_device(&sdspi_config, &out_handle); //Initialize the SD card device on the SPI bus
  esp_err_t err = sdspi_host_init(); //Initialize the SD card host driver

  if(err != ESP_OK){
    printf("Failed to initialize SD card host driver: %d\n", err);
  }
  else{
    printf("sd card successfully initialized\n");
  }

  while(true){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}