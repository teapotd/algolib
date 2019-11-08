#!/bin/bash
set -e

mkdir -p build
python3 make.py > build/algolib.tex
cd build && pdflatex algolib.tex
