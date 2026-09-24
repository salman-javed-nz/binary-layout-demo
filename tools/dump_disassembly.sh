#!/usr/bin/env bash

# Print a disassembly of the functions in each binary.

set -euo pipefail

for binary in build/layout_good build/layout_bad build/layout_bolt; do
	if [[ ! -x "${binary}" ]]; then
		continue
	fi

	output="${binary}.disassembly.asm"

	# Print functions stage_00..31.
	{
		for id in $(seq -w 0 31); do
			objdump "${binary}" \
				--section=.text \
				--disassemble="stage_${id}" \
				--no-addresses
		done
	} >"${output}"

	echo "dumped ${binary} to ${output}"
done
