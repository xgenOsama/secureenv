<?php

namespace App\Services;

use FFI;

class CFunctionFileService
{
    protected $ffi;

    public function __construct()
    {
        // Load the C library
        $this->ffi = FFI::cdef("
            bool operate(char *operation,char *source,char *dest,char *key);
        ", base_path('app/Services/file_encryptor')); // or mylib.dll for Windows
    }

    public function encryptFile($source , $dest, $key)
    {
        // Call the C function
        $saved = $this->ffi->operate("encrypt",$source,$dest,$key);
        return $saved;
    }
    public function decryptFile($source , $dest, $key)
    {
        // Call the C function
        $saved = $this->ffi->operate("decrypt",$source,$dest,$key);
        return $saved;
    }
}
