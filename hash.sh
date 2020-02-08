#!/bin/bash
cpp-7 -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-4
