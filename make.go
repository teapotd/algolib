package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
)

// 47 characters column width

var out bytes.Buffer
var pages bytes.Buffer
var captions []string

func line(buf *bytes.Buffer, str string) {
	buf.WriteString(str)
	buf.WriteString("\n")
}

func main() {
	line(&out, `\documentclass[10pt]{article}

\usepackage[a4paper,landscape,hmargin={0.5cm,0.5cm},vmargin={1cm,0.5cm},headsep=0.1cm]{geometry}
\usepackage{listings}
\usepackage{multicol}
\usepackage{titletoc}
\usepackage{courier}
\usepackage{fancyhdr}

\setlength{\columnseprule}{0.5pt}
\setlength{\columnsep}{8pt}

\lstset{language=C++}
\lstset{morekeywords={alignas,alignof,constexpr,ll,ull,ld,cmpl,rep,repd,each,all,sz,Vi,Pii,mp,mt,pb}}
\lstset{frame=t}
\lstset{tabsize=2}
\lstset{showstringspaces=false}
\lstset{breaklines=true}
\lstset{emptylines=*1}
\lstset{inputencoding=utf8}
\lstset{aboveskip=2pt}
\lstset{belowskip=0pt}
\lstset{basicstyle=\ttfamily\lst@ifdisplaystyle\scriptsize\fi}

\pagestyle{fancy}
\fancyhf{}
\renewcommand{\footrulewidth}{0pt}
\lhead{algolib}
\rhead{\thepage}
\setcounter{page}{0}

\begin{document}`)

	line(&out, `\begin{multicols*}{4}`)
	processDir("lib")
	line(&out, `\end{multicols*}\pagebreak`)

	line(&out, `\begin{multicols*}{4}`)
	out.Write(pages.Bytes())

	line(&out, `\end{multicols*}`)
	line(&out, `\end{document}`)

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
	if info.Name() == ".DS_Store" {
		return
	}

	data, err := ioutil.ReadFile(path)
	if err != nil {
		panic(err)
	}

	str := string(data)
	if strings.Contains(str, "!!IGNORE") {
		return
	}

	filtered := ""

	for _, cur := range strings.Split(str, "\n") {
		if cur == "#pragma once" {
			continue
		}
		if strings.HasPrefix(cur, "#include ") && strings.HasSuffix(cur, "template.h\"") {
			continue
		}
		// if strings.Trim(cur, " \t") == "" {
		// 	continue
		// }
		filtered += cur + "\n"
	}

	filtered = strings.Trim(filtered, " \t\n")

	caption := path[4:]
	captions = append(captions, caption)

	line(&out, fmt.Sprintf(`\noindent{\lstinline[language={}]|%s|}\hfill %d\break`, caption, len(captions)))
	line(&pages, fmt.Sprintf(`\vspace{3pt}\noindent{\textbf{\lstinline|%s|}}\hfill %d`, caption, len(captions)))

	// line(&pages, fmt.Sprintf(`\noindent{\textbf{\lstinline|%s|}}`, caption))

	if strings.HasSuffix(path, ".sh") || strings.HasSuffix(path, ".bashrc") {
		line(&pages, `\begin{lstlisting}[language=Bash]`)
	} else {
		line(&pages, `\begin{lstlisting}`)
	}
	line(&pages, filtered+`\end{lstlisting}`)
}
