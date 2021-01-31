#!/bin/bash
cpp-10 -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-4
