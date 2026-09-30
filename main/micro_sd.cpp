#include "micro_sd.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"

#define MICRO_SD_CARD_GPIO_CS (GPIO_NUM_4)

static const char* TAG = "micro_sd";

void init_sd_card()
{
    // Communication controller: Sets up the default SPI protocol parameters and a safe working speed (20MHz).
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI_BUS_HOST;

    // Device addressing: Specifies the CS (Chip Select) pin used to enable or disable communication with the SD card.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.host_id = SPI_BUS_HOST;
    slot_config.gpio_cs = MICRO_SD_CARD_GPIO_CS;

    // Filesystem config: Sets access rules, max open files, and disables automatic formatting to protect data.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = VFS_FAT_MOUNT_DEFAULT_CONFIG();
    mount_config.max_files = 1;
    mount_config.allocation_unit_size = 16 * 1024; // 16 kb

    // Card info pointer: The system automatically populates this with the card's name, size, and serial number after initialization.
    sdmmc_card_t *card;

    // MAIN MOUNT FUNCTION: Combines all configurations to initialize the card and link it to the "/sdcard" path for file access.
    ESP_LOGI(TAG, "Mounting filesystem...");
    esp_err_t ret = esp_vfs_fat_sdspi_mount(BASE_PATH, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Eroare la montare card: %s", esp_err_to_name(ret));
        return;
    }  

    else
    {
        printf("Succes: Cardul SD este gata de utilizare!\n");
    }
    ESP_LOGI(TAG, "Card montat cu succes!");
}