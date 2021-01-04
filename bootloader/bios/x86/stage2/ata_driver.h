#ifndef _BOOT_ATA_DRIVER_H
#define _BOOT_ATA_DRIVER_H

#include <stdint.h>

#define ATA_IO_REG_DATA(x)        (x + 0x0)
#define ATA_IO_REG_ERROR(x)       (x + 0x1)
#define ATA_IO_REG_FEAT(x)        (x + 0x1)
#define ATA_IO_REG_SECT_COUNT(x)  (x + 0x2)
#define ATA_IO_REG_SECT_NUM(x)    (x + 0x3)
#define ATA_IO_REG_LBA0(x)        (x + 0x3)
#define ATA_IO_REG_CYL_LO(x)      (x + 0x4)
#define ATA_IO_REG_LBA1(x)        (x + 0x4)
#define ATA_IO_REG_CYL_HI(x)      (x + 0x5)
#define ATA_IO_REG_LBA2(x)        (x + 0x5)
#define ATA_IO_REG_DRV_SEL(x)     (x + 0x6)
#define ATA_IO_REG_STATUS(x)      (x + 0x7)
#define ATA_IO_REG_COM(x)         (x + 0x7)

#define ATA_CTL_REG_ALT_STATUS 0x0
#define ATA_CTL_REG_DEV_CTL    0x0
#define ATA_CTL_REG_DRV_ADDR   0x1

#define ATA_DEV_UNKOWN 0x00
#define ATA_DEV_ATA    0x01
#define ATA_DEV_ATAPI  0x02
#define ATA_DEV_SATA   0x03
#define ATA_DEV_SATAPI 0x04

#define ATAPI_SECTOR_SIZE 2048

typedef struct ata_device {
    int io_base;
    int ctl_base;
    int slavebit;
} ata_device_t;

int ata_detect_device(ata_device_t *dev);
int ata_read_sector(ata_device_t *dev, uint32_t lba, uint8_t *buffer);

#endif // _BOOT_ATA_DRIVER_H