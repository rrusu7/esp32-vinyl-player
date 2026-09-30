#ifndef MICRO_SD_H
#define MICRO_SD_H

#include "esp_vfs_fat.h"
#include "spi_bus_config.h"

#define BASE_PATH "/sdcard"

void init_sd_card();

#endif // MICRO_SD_H