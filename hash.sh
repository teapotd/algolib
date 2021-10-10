#!/bin/bash
cpp-11 -dD -P -fpreprocessed | sed -z sg\\sggg | md5sum | cut -c-4
