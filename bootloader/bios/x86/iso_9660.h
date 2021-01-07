#ifndef _BOOT_ISO_9660_H
#define _BOOT_ISO_9660_H

#include <stdint.h>

typedef struct iso_9660_time {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t gmt_offset;
} __attribute__((packed)) iso_9660_time_t;

typedef struct iso_9660_directory {
    uint8_t len;
    uint8_t ext_attr_len;
    uint32_t lba_le;
    uint32_t lba_be;
    uint32_t data_len_le;
    uint32_t data_len_be;
    iso_9660_time_t date_time;
    uint8_t file_flags;
    uint8_t file_unit_sz;
    uint8_t interleave_gap_sz;
    uint32_t vol_seq_num;
    uint8_t file_name_len;
    char file_name[];
} __attribute__((packed)) iso_9660_directory_t;

#endif // _BOOT_ISO_9660_H