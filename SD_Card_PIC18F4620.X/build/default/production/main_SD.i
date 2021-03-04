# 1 "main_SD.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main_SD.c" 2
# 31 "main_SD.c"
# 1 "./pff3a/source/pff.h" 1
# 24 "./pff3a/source/pff.h"
# 1 "./pff3a/source/pffconf.h" 1
# 24 "./pff3a/source/pff.h" 2
# 36 "./pff3a/source/pff.h"
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 139 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 139 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3
# 36 "./pff3a/source/pff.h" 2

typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef uint16_t WORD;
typedef uint16_t WCHAR;
typedef uint32_t DWORD;
# 61 "./pff3a/source/pff.h"
typedef struct {
 BYTE fs_type;
 BYTE flag;
 BYTE csize;
 BYTE pad1;
 WORD n_rootdir;
 WORD n_fatent;
 DWORD fatbase;
 DWORD dirbase;
 DWORD database;
 DWORD fptr;
 DWORD fsize;
 WORD org_clust;
 WORD curr_clust;
 DWORD dsect;
} FATFS;





typedef struct {
 WORD index;
 BYTE* fn;
 WORD sclust;
 WORD clust;
 DWORD sect;
} DIR;





typedef struct {
 DWORD fsize;
 WORD fdate;
 WORD ftime;
 BYTE fattrib;
 char fname[13];
} FILINFO;





typedef enum {
 FR_OK = 0,
 FR_DISK_ERR,
 FR_NOT_READY,
 FR_NO_FILE,
 FR_NOT_OPENED,
 FR_NOT_ENABLED,
 FR_NO_FILESYSTEM
} FRESULT;






FRESULT pf_mount (FATFS* fs);
FRESULT pf_open (const char* path);
FRESULT pf_read (void* buff, UINT btr, UINT* br);
FRESULT pf_write (const void* buff, UINT btw, UINT* bw);
FRESULT pf_lseek (DWORD ofs);
FRESULT pf_opendir (DIR* dj, const char* path);
FRESULT pf_readdir (DIR* dj, FILINFO* fno);
FRESULT pf_close (FIL* fp);
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);
# 31 "main_SD.c" 2


FATFS FatFs;
FIL Fil;


void main(void) {
    UINT bw;




 if (pf_mount(&FatFs, "", 1) == FR_OK) {

  if (pf_open(&Fil, "test.txt", 0x10 | 0x01 | 0x02) == FR_OK) {

   if ((Fil.fsize != 0) && (f_lseek(&Fil, Fil.fsize) != FR_OK)) goto endSD;

   pf_write(&Fil, "Hello world! This is text message written to sd card\r\n", 54, &bw);

   endSD: pf_close(&Fil);
  }
 }

 while (1) {

 }
}
