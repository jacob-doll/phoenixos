import sys
import os
import math

SECTOR_SIZE = 512

def main():
    """
    Takes in three arguments:
        - first: output bootloader binary
        - second: bootsector binary code
        - third: stage2 binary code
    """
    boot_bin = sys.argv[1]
    bootsector_bin = sys.argv[2]
    stage2_bin = sys.argv[3]

    stage2_size = os.path.getsize(stage2_bin)
    boot_size = SECTOR_SIZE + stage2_size
    with open(boot_bin, 'wb') as boot_bin_file, \
         open(bootsector_bin, 'rb') as bootsector_bin_file, \
         open(stage2_bin, 'rb') as stage2_bin_file:
        boot_bin_file.write(bootsector_bin_file.read(0x1AC))
        boot_bin_file.write(stage2_size.to_bytes(4, byteorder='little'))
        bootsector_bin_file.seek(0x1B0)
        boot_bin_file.write(bootsector_bin_file.read())
        boot_bin_file.write(stage2_bin_file.read())

        fill = (math.ceil(boot_size/SECTOR_SIZE) * SECTOR_SIZE) - boot_size
        boot_bin_file.write(bytes([0 for _ in range(fill)]))

if __name__ == "__main__":
    main()