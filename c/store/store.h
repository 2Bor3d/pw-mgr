#include <stdint.h>

struct store 
{
    char *info;
    int same;
    char *salt;
    uint8_t nonce[96];
    char *data;
};

void load_file(struct store *result, char* path);
void load(struct store *result, char* input);

void serialize(struct store result);
void save(struct store result, char* path);

