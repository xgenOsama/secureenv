<?php

namespace App\Http\Controllers;

use App\Services\CFunctionService;

class CFunctionController extends Controller
{
    protected $cFunctionService;

    public function __construct(CFunctionService $cFunctionService)
    {
        $this->cFunctionService = $cFunctionService;
    }

    public function index()
    {
        // Call the C function via the service
       $DATABASE_URL =  $this->cFunctionService->getEnv("DATABASE_URL");
       $SECRET_KEY =  $this->cFunctionService->getEnv("SECRET_KEY");
       $API_KEY =  $this->cFunctionService->getEnv("API_KEY");


        return response()->json(['message' => 'Called C function successfully!',
         "DATABASE_URL" =>  $DATABASE_URL,
         "API_KEY" => $API_KEY,
         "SECRET_KEY" =>$SECRET_KEY]);
    }
}
