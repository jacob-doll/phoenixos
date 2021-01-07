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

int atapi_read_sector(ata_device_t *dev, uint32_t lba, uint8_t *buffer) {
    uint8_t read_cmd[12] = { 0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t status;
	int size;

    outb(ATA_IO_REG_DRV_SEL(dev->io_base), 0xA0 | dev->slavebit << 4);
    ata_delay(dev);

    outb(ATA_IO_REG_FEAT(dev->io_base), 0x00);
    outb(ATA_IO_REG_LBA1(dev->io_base), 2048 & 0xFF);
    outb(ATA_IO_REG_LBA2(dev->io_base), 2048 >> 8);
    outb(ATA_IO_REG_CMD(dev->io_base), 0xA0);

    while (1) {
        status = inb(ATA_IO_REG_STATUS(dev->io_base));
        if ((status & 0x01)) return -1;
		if (!(status & 0x80) && (status & 0x08)) break;
    }

	read_cmd[2] = (lba >> 0x18) & 0xFF;
	read_cmd[3] = (lba >> 0x10) & 0xFF;
	read_cmd[4] = (lba >> 0x08) & 0xFF;
	read_cmd[5] = (lba >> 0x00) & 0xFF;
    read_cmd[9] = 1;

    uint16_t* out_cmd = (uint16_t*) read_cmd;
    for (int i = 0; i < 6; i++) {
        outw(dev->io_base, out_cmd[i]);
    }

    size = (((int) inb(ATA_IO_REG_LBA2(dev->io_base))) << 8) | (int) (inb(ATA_IO_REG_LBA1(dev->io_base)));

    while (1) {
        status = inb(ATA_IO_REG_STATUS(dev->io_base));
        if ((status & 0x01)) return -1;
        if (!(status & 0x80) && (status & 0x08)) break;
    }

    insw(dev->io_base, buffer, size/2);

    while (1) {
        status = inb(ATA_IO_REG_STATUS(dev->io_base));
        if ((status & 0x01)) return -1;
        if (!(status & 0x80) && (status & 0x40)) break;
    }

    return size;
}