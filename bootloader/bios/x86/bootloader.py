import sys
import os
import math

SECTOR_SIZE = 512

def main():
    """
    Takes in three arguments:
        - first: output bootloader binary
        - second: stage2 binary code
    """
    boot_bin = sys.argv[1]
    stage2_bin = sys.argv[2]

    stage2_size = os.path.getsize(stage2_bin)
    boot_size = SECTOR_SIZE + stage2_size
    with open(boot_bin, 'wb') as boot_bin_file, \
         open(stage2_bin, 'rb') as stage2_bin_file:
        boot_bin_file.write(stage2_bin_file.read())

        fill = (math.ceil(boot_size/SECTOR_SIZE) * SECTOR_SIZE) - boot_size
        boot_bin_file.write(bytes([0 for _ in range(fill)]))

if __name__ == "__main__":
    main()