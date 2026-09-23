# Binary layout performance demo

`layout_good` and `layout_bad` use the same benchmark and algorithm source
files. `layout_bad` additionally contains code that is retained in the binary
but is never called. The linker sorts its sections between the hot algorithm
stages, spreading those stages across the executable address space.

The `benchmark` target also creates `build/bolt/layout_bolt`. It instruments
`layout_bad`, runs that temporary binary to collect a BOLT profile, and then
reorders the hot code into a layout that recovers the performance loss.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --build build --target benchmark
```

For hardware counters on Linux:

```sh
perf stat -r 5 -e cycles,instructions,cache-misses ./build/layout_good
perf stat -r 5 -e cycles,instructions,cache-misses ./build/layout_bad
perf stat -r 5 -e cycles,instructions,cache-misses ./build/bolt/layout_bolt
```

Use `nm -n` on the three binaries to compare function addresses. All programs
print the same checksum.
