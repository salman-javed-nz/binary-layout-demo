# Binary layout performance demo

This demo shows how code layout can affect performance even when program
behaviour stays the same.

- `layout_good` is the baseline.
- `layout_bad` adds unrelated code. Although this code is not executed by the
  benchmark, it still shifts the location of the hot code in the binary, slowing
  down the workload through worse instruction locality.
- `layout_bolt` uses LLVM BOLT to recover performance. By observing which parts
  of the code are actually executed, BOLT can rearrange the binary for better
  performance.

Note that in all three binaries, the code being benchmarked remains identical
down to the individual CPU instructions. The only difference is where those
instructions reside within the binary.

## Run the experiment

Build and run the baseline and disrupted binaries:

```sh
./tools/build.sh
./build/layout_good
./build/layout_bad
```

Profile `layout_bad` with BOLT to create `layout_bolt`:

```sh
./tools/run_bolt.sh
./build/layout_bolt
```

## Inspect the layout

Compare hardware counters for the three binaries:

```sh
sudo ./tools/measure_perf.sh
```

The script measures cycles, instructions, and instruction TLB misses. Note the
much higher instruction TLB misses for `layout_bad`.

Dump the symbol addresses and compare the order of the functions:

```sh
./tools/dump_layout.sh
cat build/layout_good.layout.txt
cat build/layout_bad.layout.txt
cat build/layout_bolt.layout.txt
```

Note how the unrelated code in `layout_bad` is interleaved with the hot code,
disrupting the layout.

Dump the machine code for each stage:

```sh
./tools/dump_disassembly.sh
less build/layout_good.disassembly.asm
less build/layout_bad.disassembly.asm
less build/layout_bolt.disassembly.asm
```

Note how the instructions for the hot code is the same in all three binaries.
