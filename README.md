```
put 
ffi.enable=1 
in your php.ini file and restart php and nginx
set your env vars into env.c file then compile the file with gcc
gcc -shared -o ./app/Services/env.so -fPIC env.c
```# secureenv
