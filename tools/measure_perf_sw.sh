#!/usr/bin/env bash

# Compare instruction-cache misses for whichever binaries have been built.

set -euo pipefail

for binary in build/layout_good build/layout_bad build/layout_bolt; do
	if [[ ! -x "${binary}" ]]; then
		continue
	fi

	echo "=== ${binary} ==="
	valgrind --tool=cachegrind --cache-sim=yes \
		--cachegrind-out-file=/dev/null "${binary}" 2>&1 |
		grep -E "I +refs:|I1 +misses:" | sed "s/^==[0-9]*== *//"
done
