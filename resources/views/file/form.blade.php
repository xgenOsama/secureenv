<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>File Encryption/Decryption</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
    <div class="container mt-5">
        <h2>File Encryption/Decryption</h2>

        @if(session('message'))
            <div class="alert alert-success">
                {{ session('message') }}
            </div>
        @endif

        {{-- File Encryption Form --}}
        <div class="card mb-3">
            <div class="card-body">
                <h4>Encrypt File</h4>
                <form action="{{ route('file.encrypt') }}" method="POST" enctype="multipart/form-data">
                    @csrf
                    <div class="form-group">
                        <label for="file">Select File to Encrypt</label>
                        <input type="file" name="file" id="file" class="form-control" required>
                    </div>
                    <div class="form-group">
                        <label for="key">Encryption Key (32 characters minimum)</label>
                        <input type="text" name="key" id="key" class="form-control" required minlength="32">
                    </div>
                    <button type="submit" class="btn btn-primary">Encrypt File</button>
                </form>
            </div>
        </div>

        {{-- File Decryption Form --}}
        <div class="card mb-3">
            <div class="card-body">
                <h4>Decrypt File</h4>
                <form action="{{ route('file.decrypt') }}" method="POST" enctype="multipart/form-data">
                    @csrf
                    <div class="form-group">
                        <label for="file">Select File to Decrypt</label>
                        <input type="file" name="file" id="file" class="form-control" required>
                    </div>
                    <div class="form-group">
                        <label for="key">Decryption Key</label>
                        <input type="text" name="key" id="key" class="form-control" required minlength="32">
                    </div>
                    <button type="submit" class="btn btn-primary">Decrypt File</button>
                </form>
            </div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.2/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
