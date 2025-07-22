#include <stdio.h>
#include <string.h>

#include "parson.h"
#include "store.h"

void load_file(struct store *result, char *path) {
    JSON_Value *file = json_parse_file(path);
    JSON_Object *root = json_value_get_object(file);
    result->info = (char*)json_object_get_string(root, "info");
    result->same = json_object_get_boolean(root, "same");
    result->salt = (char*)json_object_get_string(root, "salt");
    char* nonce = (char *)json_object_get_string(root, "nonce");
    result->data = (char*)json_object_get_string(root, "data");

    size_t nonce_len = strlen(nonce)+1;
    memcpy(result->nonce, nonce, nonce_len);
}

void load(struct store *result, char *input) {
    JSON_Value *value = json_parse_string(input);
    JSON_Object *object = json_value_get_object(value);

    result->info = (char*)json_object_get_string(object, "info");
    result->same = json_object_get_boolean(object, "same");
    result->salt = (char*)json_object_get_string(object, "salt");
    char* nonce = (char *)json_object_get_string(object, "nonce");
    result->data = (char*)json_object_get_string(object, "data");

    size_t nonce_len = strlen(nonce)+1;
    memcpy(result->nonce, nonce, nonce_len);
}


void serialize(struct store result) {
    JSON_Value *value = json_value_init_object();
    JSON_Object *object = json_value_get_object(value);

    char* nonce;
    memcpy(nonce, result.nonce, 96);

    json_object_set_string(object, "info", result.info);
    json_object_set_boolean(object, "same", result.same);
    json_object_set_string(object, "salt", result.salt);
    json_object_set_string(object, "nonce", nonce);
    json_object_set_string(object, "data", result.data);

    printf("%s", json_serialize_to_string(value));
}

void save(struct store result, char *path) {
    JSON_Value *value = json_value_init_object();
    JSON_Object *object = json_value_get_object(value);

    char* nonce;
    memcpy(nonce, result.nonce, 96);

    json_object_set_string(object, "info", result.info);
    json_object_set_boolean(object, "same", result.same);
    json_object_set_string(object, "salt", result.salt);
    json_object_set_string(object, "nonce", nonce);
    json_object_set_string(object, "data", result.data);

    json_serialize_to_file(value, path);
}

