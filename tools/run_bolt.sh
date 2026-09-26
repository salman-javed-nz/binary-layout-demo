#!/usr/bin/env bash

# Optimise the layout of a binary using BOLT.

set -euo pipefail

# Detect LLVM BOLT.
if command -v llvm-bolt >/dev/null 2>&1; then
	BOLT=llvm-bolt
elif [[ -x /opt/clang+llvm/bin/llvm-bolt ]]; then
	BOLT=/opt/clang+llvm/bin/llvm-bolt
else
	echo "error: llvm-bolt is not installed" >&2
	exit 1
fi

bad_binary=build/layout_bad
instrumented_binary=build/layout_bad.instrumented
profile=build/layout.fdata
optimized_binary=build/layout_bolt

# Instrument the binary.
"${BOLT}" "${bad_binary}" \
	-o "${instrumented_binary}" \
	-instrument \
	-instrumentation-file="${profile}"

# Run the instrumented binary to generate the profile.
"${instrumented_binary}"

# Optimise the binary using the generated profile.
"${BOLT}" "${bad_binary}" \
	-data "${profile}" \
	-o "${optimized_binary}" \
	-reorder-blocks=ext-tsp \
	-reorder-functions=hfsort \
	-split-functions \
	-split-all-cold
