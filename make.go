package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
)

var out bytes.Buffer

func line(str string) {
	out.WriteString(str)
	out.WriteString("\n")
}

func main() {
	line(`\documentclass[10pt]{article}

\usepackage[a4paper,landscape,hmargin={0.5cm,0.5cm},vmargin={0.4cm,0.4cm}]{geometry}
\usepackage{listings}
\usepackage{multicol}
\usepackage{titletoc}
\usepackage{courier}

\setlength{\columnseprule}{0.5pt}
\setlength{\columnsep}{10pt}

\lstset{language=C++}
\lstset{morekeywords={alignas,alignof,constexpr}}
\lstset{frame=t}
\lstset{tabsize=4}
\lstset{showstringspaces=false}
\lstset{breaklines=true}
\lstset{emptylines=*1}
\lstset{inputencoding=utf8}
\lstset{aboveskip=3pt}
\lstset{belowskip=2pt}
\lstset{basicstyle=\ttfamily\lst@ifdisplaystyle\scriptsize\fi}

\begin{document}
\begin{multicols*}{2}`)

	processDir("lib")

	line(`\end{multicols*}`)
	line(`\end{document}`)

	if err := ioutil.WriteFile("build/algolib.tex", out.Bytes(), 0777); err != nil {
		panic(err)
	}
}

func processDir(dir string) {
	files, err := ioutil.ReadDir(dir)
	if err != nil {
		panic(err)
	}

	for _, file := range files {
		if !file.IsDir() {
			processFile(filepath.Join(dir, file.Name()), file)
		}
	}

	for _, file := range files {
		if file.IsDir() {
			processDir(filepath.Join(dir, file.Name()))
		}
	}
}

func processFile(path string, info os.FileInfo) {
	if info.Name()[0] == '.' {
		return
	}

	data, err := ioutil.ReadFile(path)
	if err != nil {
		panic(err)
	}

	str := strings.Replace(string(data), "#pragma once", "", -1)
	str = strings.Replace(str, `#include "template.h"`, "", -1)
	str = strings.Replace(str, `#include "../template.h"`, "", -1)
	str = strings.Trim(str, " \n")

	line(fmt.Sprintf(`\vspace{3pt}\noindent{\textbf{\lstinline|%s|}}`, path[4:]))
	line(`\begin{lstlisting}`)
	line(str)
	line(`\end{lstlisting}`)
}
