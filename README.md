# Binary layout performance demo

`layout_good` and `layout_bad` use the same benchmark and algorithm source
file. `layout_bad` additionally contains code that is retained in the binary
but is never called. The linker sorts its sections between the hot algorithm
stages, spreading those stages across the executable address space.

`tools/run_bolt.sh` instruments `layout_bad`, runs that temporary binary to
collect a BOLT profile, and then creates `build/layout_bolt` with the hot code
reordered.

```sh
./tools/build.sh
./build/layout_good
./build/layout_bad
./tools/run_bolt.sh
./build/layout_bolt
```

The same workflow can run in Docker:

```sh
docker build -f .devcontainer/Dockerfile -t binary-layout-demo .
docker run --rm -it binary-layout-demo
```

For hardware counters on Linux:

```sh
./tools/measure_perf.sh
```

The script measures only the benchmark binaries that exist in `build/`.
If host perf permissions reject the command, run it with `sudo`:

```sh
sudo ./tools/measure_perf.sh
```

Use `nm -n` on the three binaries to compare function addresses. All programs
print the same checksum.

To dump the machine code for each stage from whichever binaries exist:

```sh
./tools/dump_disassembly.sh
less build/layout_good.disassembly.asm
less build/layout_bad.disassembly.asm
less build/layout_bolt.disassembly.asm
```

To print the complete symbol table for each binary:

```sh
./tools/dump_layout.sh
cat build/layout_good.layout.txt
cat build/layout_bad.layout.txt
cat build/layout_bolt.layout.txt
```
