#include "rc522_rfid.h"
#include "rc522.h"
#include "driver/rc522_spi.h"
#include "rc522_picc.h"
#include "esp_log.h"
#include "driver/spi_common.h"
#include "spi_bus_config.h"

#define RC522_SPI_SCANNER_GPIO_SDA (5)
#define RC522_SCANNER_GPIO_RST     (GPIO_NUM_21)

static const char* TAG = "rc522_rfid";

rc522_spi_config_t driver_config = {};

rc522_driver_handle_t driver;
rc522_handle_t scanner;

void init_driver_config()
{

  driver_config.host_id = SPI_BUS_HOST;

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
  ESP_ERROR_CHECK(rc522_spi_create(&driver_config, &driver));
  ESP_ERROR_CHECK(rc522_driver_install(driver));
}

void scanner_config()
{
  rc522_config_t scanner_config = {};
  scanner_config.driver = driver;

  ESP_ERROR_CHECK(rc522_create(&scanner_config, &scanner));
  ESP_ERROR_CHECK(rc522_register_events(scanner, RC522_EVENT_PICC_STATE_CHANGED, picc_state_changed, NULL));
}

void init_rc522() {
  init_driver_config(); //Configure the RC522 driver parameters
  spi_driver_config();  //Initialize the SPI driver and install it
  scanner_config(); //Create the RC522 scanner instance and configure it
  ESP_ERROR_CHECK(rc522_start(scanner)); //Start the RC522 scanner
}