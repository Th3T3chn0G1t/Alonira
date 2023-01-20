# TODO

- Fix licence email between Alonira sources and Genstone sources
- Mark `gen_error_t` nodiscard
- Implement CAB filesystem:
-~
| Boot Partition (FAT32)
| - Kernel image
| - Bootloader
| - KMods
-~
| Main Filesystem (CAB)
| - /Alo
|    - /Init
-~
