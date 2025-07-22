#include <stdio.h>
#include "store.h"

int main() {
    struct store result;
    load_file(&result, "test.json");
    printf("%s\n", result.info);
    serialize(result);
}

