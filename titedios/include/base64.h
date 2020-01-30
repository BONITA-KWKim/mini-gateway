#ifndef __MINI_GW_BASE_64_H__ 
#define __MINI_GW_BASE_64_H__

#include <stdlib.h>
#include <string.h>

unsigned char *__base64_encode(const unsigned char *str, int length, int *ret_length);
unsigned char *__base64_decode(const unsigned char *str, int length, int *ret_length);
unsigned char *__base64_buffer_encode(unsigned char *result, const unsigned char *str, int length, int *ret_length);
unsigned char *__base64_buffer_decode(unsigned char *result, const unsigned char *str, int length, int *ret_length);

#endif //__MINI_GW_BASE_64_H__ 
