#include "base64.h"

char* toBase64(const uint8_t* data, 
               size_t input_length, 
               size_t* output_length) {
    size_t encoded_length = 4 * ((input_length + 2) / 3);
    char* encoded_data = (char*)malloc(encoded_length + 1);
    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }

    for (size_t i = 0; i < mod_table[input_length % 3]; i++) {
        encoded_data[encoded_length - 1 - i] = '=';
    }

    encoded_data[encoded_length] = '\0';
    *output_length = encoded_length;
    return encoded_data;
}

//int main() {
//    uint8_t data[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' };
//    size_t output_length;
//    char* encoded_data = toBase64(data, sizeof(data), &output_length);

//    if (encoded_data) {
//        printf("Base64 Encoded: %s\n", encoded_data);
//        free(encoded_data);
//    } else {
//        printf("Failed to encode data.\n");
//    }

//    return 0;
//}
