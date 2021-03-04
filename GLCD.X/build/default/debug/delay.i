# 1 "delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "delay.c" 2
# 40 "delay.c"
# 1 "./delay.h" 1
# 42 "./delay.h"
# 1 "./stdutils.h" 1
# 62 "./stdutils.h"
typedef signed char sint8_t;
typedef unsigned char uint8_t;

typedef signed int sint16_t;
typedef unsigned int uint16_t;

typedef signed long int sint32_t;
typedef unsigned long int uint32_t;
# 174 "./stdutils.h"
typedef enum
{
   E_FALSE,
   E_TRUE
}Boolean_et;


typedef enum
{
    E_FAILED,
    E_SUCCESS,
    E_BUSY,
    E_TIMEOUT
}Status_et;


typedef enum
{
 E_BINARY=2,
 E_DECIMAL = 10,
 E_HEX = 16
}NumericSystem_et;
# 42 "./delay.h" 2
# 65 "./delay.h"
void DELAY_us(uint16_t us_count);
void DELAY_ms(uint16_t ms_count);
void DELAY_sec(uint16_t var_delaySecCount_u16);
# 40 "delay.c" 2
# 52 "delay.c"
void DELAY_us(uint16_t us_count)
{
    while (us_count != 0)
    {
        us_count--;
    }
}
# 70 "delay.c"
void DELAY_ms(uint16_t ms_count)
{
    while (ms_count != 0)
    {
        DELAY_us(300u);
        ms_count--;
    }
}
# 96 "delay.c"
void DELAY_sec(uint16_t sec_count)
{
    while (sec_count != 0) {
        DELAY_ms(1000);
        sec_count--;
    }
}
