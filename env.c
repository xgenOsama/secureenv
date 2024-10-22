#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold environment variable key-value pairs
typedef struct {
    const char* key; // Changed to const char*
    const char* value; // Changed to const char*
} EnvVar;

// Caesar Cipher Decryption function
void caesar_decrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Decrypt only alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' - shift + 26) % 26;  // +26 ensures positive result
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' - shift + 26) % 26;  // +26 ensures positive result
        }
    }
}

// Function to retrieve the value for a given key from the array of environment variables
const char* get_env_value(EnvVar* env_vars, int size, const char* key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(env_vars[i].key, key) == 0) {
            return env_vars[i].value; // Return the corresponding value
        }
    }
    return NULL; // Return NULL if the key is not found
}

const char* get_env(char* key) {
    // Create an array of environment variables with encrypted values
    EnvVar env_vars[] = {
        {"DATABASE_URL", "pbvto://xvhu:sdvvzrug@orfdokrvw/geqdph"},  // Example encrypted value
        {"SECRET_KEY", "pbzqjxnryb|"},  // Example encrypted value
        {"API_KEY", "4567890abcdef|"},  // Example encrypted value
        {"ENCRYPTION_KEY", "yrqkcrlqeym|"}  // Example encrypted value
    };

    // Decrypt the values in the environment variable array
    int shift = 3; // Shift value for decryption
    for (int i = 0; i < sizeof(env_vars) / sizeof(env_vars[0]); i++) {
        char* decrypted_value = strdup(env_vars[i].value); // Duplicate value for decryption
        caesar_decrypt(decrypted_value, strlen(decrypted_value), shift);
        env_vars[i].value = decrypted_value; // Assign decrypted value back
    }

    int size = sizeof(env_vars) / sizeof(env_vars[0]);

    // Get the value from the array
    const char* value = get_env_value(env_vars, size, key);
    if (value) {
        return value;
    } else {
        return NULL;
    }
}

// Example usage
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    const char* result = get_env(argv[1]);
    if (result) {
        printf("Value: %s\n", result);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}
