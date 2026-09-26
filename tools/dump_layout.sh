#!/usr/bin/env bash

# Print the order and addresses of functions in each binary.

set -euo pipefail

for binary in build/layout_good build/layout_bad build/layout_bolt; do
	if [[ ! -x "${binary}" ]]; then
		continue
	fi

	output="${binary}.layout.txt"
	nm --numeric-sort --defined-only "${binary}" >"${output}"

	echo "dumped ${binary} to ${output}"
done
