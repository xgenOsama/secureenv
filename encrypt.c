#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHIFT 3  // Number of positions to shift

// Caesar Cipher Encryption function
void caesar_encrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        // Encrypt only alphabetical characters
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' + shift) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' + shift) % 26;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <value_to_encrypt>\n", argv[0]);
        return 1;
    }

    // Get the value to encrypt from the command-line argument
    char* value = argv[1];
    size_t length = strlen(value);

    // Encrypt the value using the Caesar Cipher function
    caesar_encrypt(value, length, SHIFT);

    // Print the encrypted value
    printf("Encrypted Value: %s\n", value);

    return 0;
}

