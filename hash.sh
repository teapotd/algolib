#!/bin/bash
set -e -o pipefail
cpp -dD -P -fpreprocessed | sed -z sg\\sggg | md5sum | cut -c-4
