#include "ata_driver.h"
#include "ports.h"
#include "vga_text.h"

static void ata_delay(ata_device_t *dev) {
    inb(dev->ctl_base);
    inb(dev->ctl_base);
    inb(dev->ctl_base);
    inb(dev->ctl_base);
}

static void ata_software_reset(ata_device_t *dev) {
    outb(dev->ctl_base, 0x04);
    ata_delay(dev);
    outb(dev->ctl_base, 0x00);
}

int ata_detect_device(ata_device_t *dev) {
    ata_software_reset(dev);
    outb(ATA_IO_REG_DRV_SEL(dev->io_base), 0xA0 | dev->slavebit << 4);
    ata_delay(dev);
    unsigned cl = inb(ATA_IO_REG_CYL_LO(dev->io_base));
    unsigned ch = inb(ATA_IO_REG_CYL_HI(dev->io_base));

    if (cl == 0x14 && ch == 0xEB) return ATA_DEV_ATAPI;
    if (cl == 0x69 && ch == 0x96) return ATA_DEV_SATAPI;
    if (cl == 0x00 && ch == 0x00) return ATA_DEV_ATA;
    if (cl == 0x3C && ch == 0xC3) return ATA_DEV_SATA;
    return ATA_DEV_UNKOWN;
}

int ata_read_sector(ata_device_t *dev, uint32_t lba, uint8_t *buffer) { 
    lba &= 0x0FFFFFFF;

    outb(ATA_IO_REG_DRV_SEL(dev->io_base), 0xE0 | (dev->slavebit << 4) | ((lba >> 24) & 0x0F));
    outb(ATA_IO_REG_SECT_COUNT(dev->io_base), 0x01);
    outb(ATA_IO_REG_LBA0(dev->io_base), lba & 0xFF);
    outb(ATA_IO_REG_LBA1(dev->io_base), (lba >> 8) & 0xFF);
    outb(ATA_IO_REG_LBA2(dev->io_base), (lba >> 16) & 0xFF);
    outb(ATA_IO_REG_COM(dev->io_base), 0x20);

    while (1) {
        uint8_t in = inb(ATA_IO_REG_STATUS(dev->io_base));
        if (in & 0x08) break;
    }

    insw(ATA_IO_REG_DATA(dev->io_base), buffer, 256);

    return 0;     
}