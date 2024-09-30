<?php

namespace App\Http\Controllers;

use App\Services\CFunctionFileService;
use App\Services\CFunctionService;
use App\Services\FileEncryptionService;
use Illuminate\Http\Request;

class FileController extends Controller
{
    protected $fileEncryptionService;
    protected $cFunctionService;
    protected $cFunctionFileService;

    public function __construct(FileEncryptionService $fileEncryptionService,
                                CFunctionService $cFunctionService,
                                CFunctionFileService $cFunctionFileService)
    {
        $this->fileEncryptionService = $fileEncryptionService;
        $this->cFunctionService = $cFunctionService;
        $this->cFunctionFileService = $cFunctionFileService;
    }

       // Display the file upload form
       public function showUploadForm()
       {
           return view('file.form');
       }

    public function encryptFile(Request $request)
    {
        $source = $request->file('file'); // assuming file input
        $destination = storage_path('app/encrypted_file.enc');
        $key =  $this->cFunctionService->getEnv("API_KEY");
        //$key = 'your-encryption-key-file-test'; // Use proper key management

        $this->fileEncryptionService->encryptFile($source->getPathname(), $destination, $key);
        $this->cFunctionFileService->encryptFile(storage_path('app/decrypted_file.png'),storage_path('app/image_c_lang.enc'),"12345678901234567890123456789012");
        return response()->json(['message' => 'File encrypted successfully.']);
    }

    public function decryptFile(Request $request)
    {
        $source = storage_path('app/encrypted_file.enc');
        $destination = storage_path('app/decrypted_file.png');
        //$key = 'your-encryption-key-file-test'; // Use proper key management
        $key =  $this->cFunctionService->getEnv("API_KEY");
        $this->fileEncryptionService->decryptFile($source, $destination, $key);
        $this->cFunctionFileService->decryptFile(storage_path('app/image_c_lang.enc'),storage_path('app/image_c_lang.png'),"12345678901234567890123456789012");

        return response()->json(['message' => 'File decrypted successfully.']);
    }
}
