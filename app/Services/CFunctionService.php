<?php

namespace App\Services;

use FFI;

class CFunctionService
{
    protected $ffi;

    public function __construct()
    {
        // Load the C library
        $this->ffi = FFI::cdef("
            char* get_env(char* key);
        ", base_path('app/Services/env.so')); // or mylib.dll for Windows
    }

    public function getEnv($key)
    {
        // Call the C function
        return FFI::string($this->ffi->get_env($key));
    }
}
