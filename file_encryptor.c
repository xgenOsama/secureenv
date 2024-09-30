#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>  // Include stdint.h for uint8_t

#define FILE_ENCRYPTION_BLOCKS 10000
#define CIPHER EVP_aes_256_cbc()

bool encryptFile(const char *source, const char *dest, const  char *key)
{
    FILE *fpSource = fopen(source, "rb");
    FILE *fpDest = fopen(dest, "wb");

    if (!fpSource || !fpDest) {
        fprintf(stderr, "File error.\n");
        return false;
    }

    const EVP_CIPHER *cipher = CIPHER;
    int ivLength = EVP_CIPHER_iv_length(cipher);
    unsigned char iv[ivLength];

    // Generate a random IV and write it to the destination file
    if (!RAND_bytes(iv, ivLength)) {
        fprintf(stderr, "Could not generate random IV.\n");
        return false;
    }
    fwrite(iv, 1, ivLength, fpDest);
    uint8_t keyy[32];
    memcpy(keyy, key, 32);  // Copy the key to the uint8_t array

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, cipher, NULL, keyy, iv);

    unsigned char buffer[ivLength * FILE_ENCRYPTION_BLOCKS];
    unsigned char cipherBuffer[ivLength * (FILE_ENCRYPTION_BLOCKS + 1)];
    int bytesRead, cipherLen;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fpSource)) > 0) {
        if (!EVP_EncryptUpdate(ctx, cipherBuffer, &cipherLen, buffer, bytesRead)) {
            fprintf(stderr, "Encryption failed.\n");
            return false;
        }
        fwrite(cipherBuffer, 1, cipherLen, fpDest);
    }

    if (!EVP_EncryptFinal_ex(ctx, cipherBuffer, &cipherLen)) {
        fprintf(stderr, "Final encryption step failed.\n");
        return false;
    }
    fwrite(cipherBuffer, 1, cipherLen, fpDest);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fpSource);
    fclose(fpDest);

    return true;
}

bool decryptFile(const char *source, const char *dest, const  char *key)
{
    FILE *fpSource = fopen(source, "rb");
    FILE *fpDest = fopen(dest, "wb");

    if (!fpSource || !fpDest) {
        fprintf(stderr, "File error.\n");
        return false;
    }

    const EVP_CIPHER *cipher = CIPHER;
    int ivLength = EVP_CIPHER_iv_length(cipher);
    unsigned char iv[ivLength];

    // Read the IV from the source file
    fread(iv, 1, ivLength, fpSource);
    uint8_t keyy[32];
    memcpy(keyy, key, 32);  // Copy the key to the uint8_t array
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, cipher, NULL, keyy, iv);

    unsigned char buffer[ivLength * (FILE_ENCRYPTION_BLOCKS + 1)];
    unsigned char plainBuffer[ivLength * FILE_ENCRYPTION_BLOCKS];
    int bytesRead, plainLen;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fpSource)) > 0) {
        if (!EVP_DecryptUpdate(ctx, plainBuffer, &plainLen, buffer, bytesRead)) {
            fprintf(stderr, "Decryption failed.\n");
            return false;
        }
        fwrite(plainBuffer, 1, plainLen, fpDest);
    }

    if (!EVP_DecryptFinal_ex(ctx, plainBuffer, &plainLen)) {
        fprintf(stderr, "Final decryption step failed.\n");
        return false;
    }
    fwrite(plainBuffer, 1, plainLen, fpDest);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fpSource);
    fclose(fpDest);

    return true;
}

bool operate(char *operation,char *source,char *dest,char *key)
{
    if (strlen((char *)key) != 32) {
        fprintf(stderr, "Key must be 32 bytes (256 bits) long for AES-256.\n");
        return false;
    }
    if (strcmp(operation, "encrypt") == 0) {
        return encryptFile(source, dest, key);
    } else if (strcmp(operation, "decrypt") == 0) {
        return decryptFile(source, dest, key);
    } else {
        fprintf(stderr, "Invalid operation: %s. Use 'encrypt' or 'decrypt'.\n", operation);
        return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    // Implementation here
}