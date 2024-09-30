#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold environment variable key-value pairs
typedef struct {
    char* key;
    char* value;
} EnvVar;

// Function to retrieve the value for a given key from the array of environment variables
char* get_env_value(EnvVar* env_vars, int size, const char* key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(env_vars[i].key, key) == 0) {
            return env_vars[i].value; // Return the corresponding value
        }
    }
    return NULL; // Return NULL if the key is not found
}

char* get_env(char* key) {
    // Create an array of environment variables
    EnvVar env_vars[] = {
        {"DATABASE_URL", "mysql://user:password@localhost/dbname"},
        {"SECRET_KEY", "mysecretkey"},
        {"API_KEY", "1234567890abcdef"},
        {"ENCRYPTION_KEY", "your-encryption-key-file-test"},
    };

    int size = sizeof(env_vars) / sizeof(env_vars[0]);

    // Get the key from the command-line arguments
    const char* key_to_find = key;

    // Get the value from the array
    char* value = get_env_value(env_vars, size, key_to_find);
    if (value) {
       return value;
    } else {
       return NULL;
    }

    return NULL;
}