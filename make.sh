#!/bin/bash
set -e

mkdir -p build
python3 make.py > build/algolib.tex
cd build && pdflatex --shell-escape algolib.tex && pdflatex --shell-escape algolib.tex
