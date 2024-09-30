<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\CFunctionController;
use App\Http\Controllers\FileController;


/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider and all of them will
| be assigned to the "web" middleware group. Make something great!
|
*/

// Route::get('/', function () {
//     return view('welcome');
// });
Route::get('/', [CFunctionController::class, 'index']);

Route::get('/file', [FileController::class, 'showUploadForm'])->name('file.form');
Route::post('/file/encrypt', [FileController::class, 'encryptFile'])->name('file.encrypt');
Route::get('/file/decrypt', [FileController::class, 'decryptFile'])->name('file.decrypt');