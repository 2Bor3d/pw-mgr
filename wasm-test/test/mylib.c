#include <stdlib.h>
#include <string.h>

// Function to process a string
char* process_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 50); // Allocate extra space
    
    if (result == NULL) {
        return NULL;
    }
    
    strcpy(result, "Processed: ");
    strcat(result, input);
    strcat(result, " (WASM)");
    
    return result;
}

// Function to free memory allocated by process_string
void free_string(char* str) {
    if (str != NULL) {
        free(str);
    }
}

// Another example function
char* reverse_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = input[len - 1 - i];
    }
    result[len] = '\0';
    
    return result;
}

