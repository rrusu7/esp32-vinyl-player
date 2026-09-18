#include "rc522_rfid.h"
#include "rc522.h"
#include "driver/rc522_spi.h"
#include "rc522_picc.h"
#include "esp_log.h"
#include "driver/spi_common.h"

spi_bus_config_t bus_config = {};
rc522_spi_config_t driver_config = {};

rc522_driver_handle_t driver;
rc522_handle_t scanner;

void init_bus_config()
{
  bus_config.mosi_io_num = RC522_SPI_BUS_GPIO_MOSI;
  bus_config.miso_io_num = RC522_SPI_BUS_GPIO_MISO;
  bus_config.sclk_io_num = RC522_SPI_BUS_GPIO_SCLK;

  bus_config.quadhd_io_num = -1;
  bus_config.quadwp_io_num = -1;
}

void init_driver_config()
{

  driver_config.host_id = SPI3_HOST;
  driver_config.bus_config = &bus_config;

  driver_config.dev_config = {};
  driver_config.dev_config.spics_io_num = RC522_SPI_SCANNER_GPIO_SDA;
  // driver_config.dev_config.clock_speed_hz = 5000000; // 5 MHz, sub max 10MHz al MFRC522
  // driver_config.dev_config.mode = 0;
  // driver_config.dev_config.queue_size = 7;

  driver_config.dma_chan = SPI_DMA_DISABLED; // Do not enable DMA for SPI
  driver_config.rst_io_num = RC522_SCANNER_GPIO_RST;
}

void picc_state_changed(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
  rc522_picc_state_changed_event_t *event = (rc522_picc_state_changed_event_t *)event_data;
  rc522_picc_t *picc = event->picc;

  if (picc->state == RC522_PICC_STATE_ACTIVE)
  {
    rc522_picc_print(picc);
  }
  else if (picc->state == RC522_PICC_STATE_IDLE && event->old_state == RC522_PICC_STATE_ACTIVE)
  {
    ESP_LOGI(TAG, "Card has been removed");
  }
}

void spi_driver_config()
{
  rc522_spi_create(&driver_config, &driver);
  rc522_driver_install(driver);
}

void scanner_config()
{
  rc522_config_t scanner_config = {};
  scanner_config.driver = driver;

  rc522_create(&scanner_config, &scanner);
  rc522_register_events(scanner, RC522_EVENT_PICC_STATE_CHANGED, picc_state_changed, NULL);
}