To diagnose a segfault, start by compiling for debugging:
```shell
# Using your favorite compiler
c++ -g [command]
cc -g [command]
gcc -g [command]
# CMake is a little different
cmake -DCMAKE_BUILD_TYPE=Debug [command]
cmake -DCMAKE_BUILD_TYPE=RekWithDebInfo [command] # Also does release optimizations
```
After compiling and linking, run the executable with:
```shell
gdb ./main.o
```
And press `r`.
