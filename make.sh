#!/bin/bash
set -e

mkdir -p build
python3 generate-latex.py > build/algolib.tex
cd build && latexmk -pdf -shell-escape algolib.tex
