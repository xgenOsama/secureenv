```
put 
ffi.enable=1 
in your php.ini file and restart php and nginx
set your env vars into env.c file then compile the file with gcc
gcc -shared -o ./app/Services/env.so -fPIC env.c


you can also but in /usr/local/bin/
sudo gcc -shared -o /usr/local/bin/env_lara -fPIC env.c
and refrence it like that 
$this->ffi = FFI::cdef("
    char* get_env(char* key);
", "/usr/local/bin/env_lara"); 
```# secureenv
