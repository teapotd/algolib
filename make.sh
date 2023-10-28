#!/bin/bash
set -e

python3 generate-latex.py > doc/content.tex
mkdir -p build
cp doc/* build/
cd build && latexmk -pdf -shell-escape algolib.tex
