#!/bin/bash
set -e -o pipefail

mkdir -p ../build/coverage
gcovr --root ../src/ --object-directory ../build/  \
      --html-details ../build/coverage/index.html  \
      --html-tab-size=2 --merge-mode-functions=separate
