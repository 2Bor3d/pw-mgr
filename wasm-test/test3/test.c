#include "hash/argon2.h"
#include "crypt/chacha.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHLEN 32
#define SALTLEN 16

#define T_COST 2
#define M_COST 16
#define PARALLELISM 1

char* hash_encoded(char* salt, char* password) {
    const uint8_t* password_converted = (uint8_t*)password;
    uint8_t salt_converted[SALTLEN];
    memcpy(salt_converted, salt, SALTLEN);

    size_t encodedlen = argon2_encodedlen(T_COST, M_COST, PARALLELISM, SALTLEN, HASHLEN, Argon2_i);
    char* result = (char*)malloc(encodedlen+10);
    *result = '\0';

    argon2i_hash_encoded(T_COST, M_COST, PARALLELISM, password_converted, strlen(password), salt_converted, SALTLEN, HASHLEN, result, encodedlen);

    printf("%s\n", result);
    return result;
}

int is_null_terminated(const char* str, size_t buffer_size) {
    // Scan up to buffer_size looking for '\0'
    for (size_t i = 0; i < buffer_size; i++) {
        if (str[i] == '\0') {
            return 1;  // Found null terminator
        }
    }
    return 0;  // No null terminator found within buffer
}

char* hash(char* salt, char* password) {
    printf("salt: %s\n", salt);
    printf("password: %s\n", password);
    printf("hashlen: %i\n", HASHLEN);
    // convert the inputs to the requred types
    const uint8_t* password_converted = (uint8_t*)password;
    uint8_t salt_converted[SALTLEN];
    memcpy(salt_converted, salt, SALTLEN);

    uint8_t result_raw[HASHLEN];

    argon2i_hash_raw(T_COST, M_COST, PARALLELISM, password_converted, strlen(password), salt_converted, SALTLEN, &result_raw, HASHLEN);

    char* result_char = (char*)result_raw;
    printf("%s\n", result_char);
    printf("Null-terminated: %i\n", is_null_terminated(result_char, HASHLEN+1));
    result_char[HASHLEN] = '\0';

    // print result for debugging
    for( int i=0; i<HASHLEN; ++i ) printf( "%02x", result_raw[i] ); printf( "\n" );

    // convert result into char*
    char* return_result = (char*)malloc(strlen(result_char)*sizeof(char));
    printf("Size: %lu\n", strlen(result_char));
    printf("Char size: %lu\n", sizeof(char));
    //char* return_result = (char*)malloc(33*sizeof(char));
    memcpy(return_result, result_char, strlen(result_char));

    // test if conversion was successfull
    uint8_t test[HASHLEN];
    memcpy(test, return_result, HASHLEN);
    for( int i=0; i<HASHLEN; ++i ) printf( "%02x", test[i] ); printf( "\n" );

    return return_result;
}

char* crypt(char* input, char* key) {
    printf("%s\n", key);
    const size_t length = strlen(input);
    unsigned char* output = (unsigned char*)malloc(length*sizeof(unsigned char));
    const unsigned int counter[4] = {0, 0, 0, 1};

    size_t key_size = (strlen(key)+sizeof(unsigned int)-1) /
        sizeof(unsigned int);
    printf("Key size: %lu\n", key_size);
    printf("Unsigned int size: %lu\n", sizeof(unsigned int));
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
    char* salt = "AAAAAAAAAAAAAAAA";
    char* password = "password";
    char* key = hash(salt, password);
    printf("%s\n", key);
    printf("%s\n", hash_encoded(salt, password));
    printf("-----------\n");

    char* text = "Hello world!";
    printf("%s\n", crypt(text, key));
    printf("%s\n", crypt(crypt(text, key), key));
    free(key);

    return 0;
}

