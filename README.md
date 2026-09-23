# Binary layout performance demo

Both executables use the same benchmark and algorithm source files.
`layout_bad` additionally contains code that is retained in the binary but is
never called. The linker sorts its sections between the hot algorithm stages,
spreading those stages across the executable address space.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --build build --target benchmark
```

For hardware counters on Linux:

```sh
perf stat -r 5 -e cycles,instructions,cache-misses ./build/layout_good
perf stat -r 5 -e cycles,instructions,cache-misses ./build/layout_bad
```

Use `nm -n build/layout_good` and `nm -n build/layout_bad` to compare function
addresses. Both programs print the same checksum.
