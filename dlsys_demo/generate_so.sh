rm -fr *.so
gcc -fPIC -shared caculate1.c -o libcaculate1.so
gcc -fPIC -shared caculate.c -o libcaculate.so