#include <stdlib.h>
#include <string.h>
#include "chacha.h"

#include <stdio.h>

static const unsigned int key[] = {
    0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
    0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c
};

char* crypt(char* input, char* key) {
    const size_t length = strlen(input);
    unsigned char* output = (unsigned char*)malloc(sizeof(*input));
    const unsigned int counter[4] = {0, 0, 0, 1};

    size_t key_size = (strlen(key)+sizeof(unsigned int)-1) /
        sizeof(unsigned int);
    unsigned int* key_int = malloc(key_size*sizeof(unsigned int));
    memcpy(key_int, key, strlen(key));
    for (size_t i = 0; i < key_size; i++) {
        printf("int_array[%zu] = 0x%08x\n", i, key_int[i]);
    }

    ChaCha20_ctr32(output, 
            (unsigned char*)input, 
            strlen(input), 
            key_int, 
            counter);

    return (char*)output;
}

int main() {
    const unsigned char* input = (unsigned char*)"Hello world";
    unsigned char* output = (unsigned char*)malloc(sizeof(*input));
    const size_t len = strlen((char*)input);
    const unsigned int counter[4] = {0, 0, 0, 1};
    ChaCha20_ctr32(output, input, len, key, counter);
    printf("1: %s\n", output);

    unsigned char* final = (unsigned char*)malloc(sizeof(*input));
    ChaCha20_ctr32(final, output, len, key, counter);
    printf("2: %s\n", final);
    printf("--------\n");

    printf("%s\n", crypt(crypt("Hello world", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}
