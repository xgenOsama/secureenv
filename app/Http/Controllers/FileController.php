<?php

namespace App\Http\Controllers;

use App\Services\CFunctionService;
use App\Services\FileEncryptionService;
use Illuminate\Http\Request;

class FileController extends Controller
{
    protected $fileEncryptionService;
    protected $cFunctionService;


    public function __construct(FileEncryptionService $fileEncryptionService,CFunctionService $cFunctionService)
    {
        $this->fileEncryptionService = $fileEncryptionService;
        $this->cFunctionService = $cFunctionService;
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

        return response()->json(['message' => 'File encrypted successfully.']);
    }

    public function decryptFile(Request $request)
    {
        $source = storage_path('app/encrypted_file.enc');
        $destination = storage_path('app/decrypted_file.png');
        //$key = 'your-encryption-key-file-test'; // Use proper key management
        $key =  $this->cFunctionService->getEnv("API_KEY");
        $this->fileEncryptionService->decryptFile($source, $destination, $key);

        return response()->json(['message' => 'File decrypted successfully.']);
    }
}
