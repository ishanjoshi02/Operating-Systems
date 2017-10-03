## Compile the Program

This program uses the PThread Library. This library is not included implicitly by GNU Cross Compiler (GCC).
Pass `-pthread` while compiling.

`gcc -pthread -o object_file assignment3.c`
`./object_file`
