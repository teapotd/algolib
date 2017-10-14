#!/bin/bash
set -e

go run make.go
cd build && pdflatex algolib.tex
