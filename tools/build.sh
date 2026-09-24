#!/usr/bin/env bash

# Configure and build the demo.

set -euo pipefail

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
