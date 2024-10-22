#include <stdio.h>
#include <string.h>

#define MAX_VARS 4 // increase this for the number of env vars
#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 100

// Define the environment variables as separate arrays
char env_keys[MAX_VARS][MAX_KEY_LENGTH] = {
    "DATABASE_URL",
    "SECRET_KEY",
    "API_KEY",
    "ENCRYPTION_KEY"
};

char env_values[MAX_VARS][MAX_VALUE_LENGTH] = {
    "mysql://user:password@localhost/dbname",
    "mysecretkey",
    "1234567890abcdef",
    "your-encryption-key-file-test"
};

// Function to retrieve the value for a given key
char* get_env(char* key) {
    for (int i = 0; i < MAX_VARS; i++) {
        if (strcmp(env_keys[i], key) == 0) {
            return env_values[i]; // Return the corresponding value
        }
    }
    return NULL; // Return NULL if the key is not found
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    char* value = get_env_value(argv[1]);
    if (value) {
        printf("Value: %s\n", value);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}
