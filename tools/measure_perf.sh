#!/usr/bin/env bash

# Compare hardware counters for whichever binaries have been built.

set -euo pipefail

for binary in build/layout_good build/layout_bad build/layout_bolt; do
	if [[ ! -x "${binary}" ]]; then
		continue
	fi
	perf stat --event=cycles,instructions,iTLB-load-misses -- "${binary}"
done
