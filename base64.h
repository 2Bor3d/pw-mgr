// base64.h
#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static const char base64_table[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const int mod_table[] = {0, 2, 1};

char* toBase64(const uint8_t* data, 
               size_t input_length, 
               size_t* output_length);

#endif // BASE64_H
