

#ifndef _UTILITIES_H
#define _UTILITIES_H
#ifdef __cplusplus
    extern "C" {
#endif
#include "stdio.h"
#include "bts_frame_message.h"
typedef union 
{
	float data_float;
	uint8_t bytes[4];	
} data_format_float_bytes;

typedef union 
{
    uint32_t data_int;
    uint8_t bytes[4];
} data_format_int_bytes;

typedef union 
{
    uint16_t data_uint16;
    uint8_t bytes[2];
} data_format_uint8_16_t;


#ifdef __cplusplus
}
#endif

#endif
