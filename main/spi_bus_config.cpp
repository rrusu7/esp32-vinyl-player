#include "spi_bus_config.h"
#include "driver/spi_common.h"
#include "driver/sdspi_host.h"
#include "esp_log.h"

#define SPI_BUS_GPIO_MISO    (19)
#define SPI_BUS_GPIO_MOSI    (23)
#define SPI_BUS_GPIO_SCLK    (18)

static const char* TAG = "spi_bus_config";

void init_bus_config()
{
    // Hardware bus config: Assigns the physical ESP32 pins (MOSI, MISO, CLK) to handle the SPI data stream.
    spi_bus_config_t bus_config = {};
        bus_config.miso_io_num = SPI_BUS_GPIO_MISO;
        bus_config.mosi_io_num = SPI_BUS_GPIO_MOSI;
        bus_config.sclk_io_num = SPI_BUS_GPIO_SCLK;
        bus_config.quadwp_io_num = -1;
        bus_config.quadhd_io_num = -1;
        bus_config.max_transfer_sz = 4000;

    // Physically initializes the designated pins on the chosen SPI peripheral.
    esp_err_t ret = spi_bus_initialize(SPI_BUS_HOST, &bus_config, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
    {
        ESP_LOGE("MAIN", "Nu s-a putut initializa magistrala SPI");
        return;
    }
}