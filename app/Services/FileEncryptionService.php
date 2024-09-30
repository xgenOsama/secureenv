<?php

namespace App\Services;

use Exception;

class FileEncryptionService
{
    const FILE_ENCRYPTION_BLOCKS = 10000;

    protected $cipher = 'aes-256-cbc';

    /**
     * Encrypt the given file.
     *
     * @param string $source Path of the unencrypted file.
     * @param string $dest Path of the encrypted file to be created.
     * @param string $key Encryption key.
     * @return void
     * @throws Exception
     */
    public function encryptFile(string $source, string $dest, string $key)
    {
        $ivLength = openssl_cipher_iv_length($this->cipher);
        $iv = openssl_random_pseudo_bytes($ivLength);

        $fpSource = fopen($source, 'rb');
        $fpDest = fopen($dest, 'w');

        // Write the IV at the beginning of the destination file
        fwrite($fpDest, $iv);

        while (!feof($fpSource)) {
            $plaintext = fread($fpSource, $ivLength * self::FILE_ENCRYPTION_BLOCKS);
            $ciphertext = openssl_encrypt($plaintext, $this->cipher, $key, OPENSSL_RAW_DATA, $iv);
            $iv = substr($ciphertext, 0, $ivLength);

            fwrite($fpDest, $ciphertext);
        }

        fclose($fpSource);
        fclose($fpDest);
    }

    /**
     * Decrypt the given file.
     *
     * @param string $source Path of the encrypted file.
     * @param string $dest Path of the decrypted file to be created.
     * @param string $key Encryption key.
     * @return void
     * @throws Exception
     */
    public function decryptFile(string $source, string $dest, string $key)
    {
        $ivLength = openssl_cipher_iv_length($this->cipher);

        $fpSource = fopen($source, 'rb');
        $fpDest = fopen($dest, 'w');

        // Read the IV from the beginning of the source file
        $iv = fread($fpSource, $ivLength);

        while (!feof($fpSource)) {
            $ciphertext = fread($fpSource, $ivLength * (self::FILE_ENCRYPTION_BLOCKS + 1));
            $plaintext = openssl_decrypt($ciphertext, $this->cipher, $key, OPENSSL_RAW_DATA, $iv);
            $iv = substr($plaintext, 0, $ivLength);

            fwrite($fpDest, $plaintext);
        }

        fclose($fpSource);
        fclose($fpDest);
    }
}
