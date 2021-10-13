#!/bin/bash
set -e -o pipefail
cpp-11 -dD -P -fpreprocessed | sed -z sg\\sggg | md5sum | cut -c-4
