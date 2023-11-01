#!/bin/bash
set -e

mkdir -p build
python3 generate-latex.py > doc/content.tex
cp doc/* build/
cd build && latexmk -pdf -shell-escape algolib.tex
