#!/bin/bash
set -e -o pipefail

find ../build/tests/ -name '*.gcda' -delete -or -name '*.gcno' -delete
