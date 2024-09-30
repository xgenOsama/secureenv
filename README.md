```
# put 
ffi.enable=1 
# in your php.ini file and restart php and nginx
# set your env vars into env.c file then compile the file with gcc
gcc -shared -o ./app/Services/env.so -fPIC env.c
brew install openssl
export LDFLAGS="-L/usr/local/opt/openssl/lib"
export CPPFLAGS="-I/usr/local/opt/openssl/include"
export LDFLAGS="-L/opt/homebrew/lib"
export CPPFLAGS="-I/opt/homebrew/include"
gcc -o ./app/Services/file_encryptor file_encryptor.c -lssl -lcrypto
gcc -o ./app/Services/file_encryptor file_encryptor.c -I/opt/homebrew/include -L/opt/homebrew/lib -lssl -lcrypto




# you can also but in /usr/local/bin/
sudo gcc -shared -o /usr/local/bin/env_lara -fPIC env.c
sudo chmod 711 /usr/local/bin/env_lara # only allow execute of the file but not copy it (only root access)
cp /usr/local/bin/env_lara ~/
cp: /usr/local/bin/env_lara: Permission denied

# and refrence it like that in the service 

$this->ffi = FFI::cdef("
    char* get_env(char* key);
", "/usr/local/bin/env_lara"); 
```# secureenv
