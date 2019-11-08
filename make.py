import os

FILE_TEMPLATE = r'''
\documentclass[10pt]{article}

\usepackage[a4paper,landscape,hmargin={0.5cm,0.5cm},vmargin={1.2cm,0.9cm},headsep=0.1cm]{geometry}
\usepackage{listings}
\usepackage{multicol}
\usepackage{titletoc}
\usepackage{courier}
\usepackage{fancyhdr}
\usepackage{minted}
\usepackage{ulem}

\setlength{\columnseprule}{0.5pt}
\setlength{\columnsep}{8pt}

\lstset{frame=t}
\lstset{tabsize=2}
\lstset{showstringspaces=false}
\lstset{breaklines=true}
\lstset{emptylines=*1}
\lstset{inputencoding=utf8}
\lstset{aboveskip=2pt}
\lstset{belowskip=0pt}
\lstset{basicstyle=\ttfamily\lst@ifdisplaystyle\scriptsize\fi}

\setminted{tabsize=2}
\setminted{fontsize=\scriptsize}

\pagestyle{fancy}
\fancyhf{}
\renewcommand{\footrulewidth}{0pt}
\lhead{algolib}
\rhead{\thepage}
\setcounter{page}{0}

\begin{document}

\begin{multicols*}{4}
%s
\end{multicols*}\pagebreak

\begin{multicols*}{4}
%s
\end{multicols*}

\end{document}
'''

def main():
	global captions, content, file_count
	captions, content, file_count = '', '', 0
	process_dir('src')
	print(FILE_TEMPLATE % (captions, content))

def process_dir(dir):
	entries = [os.path.join(dir, s) for s in os.listdir(dir)]
	entries.sort()

	for entry in entries:
		if not os.path.isdir(entry):
			process_file(entry)

	for entry in entries:
		if os.path.isdir(entry):
			process_dir(entry)

def process_file(path):
	if os.path.basename(path) == '.DS_Store':
		return

	with open(path, 'r') as file:
		data = file.read()

	if '!!IGNORE' in data:
		return

	lines = []

	for line in data.split('\n'):
		if line == '#pragma once':
			continue
		if line.startswith('#include ') and 'template.h' in line:
			continue
		if line.startswith('//!'):
			continue
		lines.append(line)

	global captions, content, file_count
	title = path[path.index('/')+1:]
	data = '\n'.join(lines).strip()
	file_count += 1

	lang = 'cpp'
	if path.endswith('.bashrc'):
		lang = 'bash'
	elif path.endswith('.vimrc'):
		lang = 'vim'

	captions += r'\noindent{\lstinline|%s|}\hfill %d\break' % (title, file_count) + '\n'

	content += r'\noindent{\uline{\textbf{\lstinline|%s|}\hfill %d}}\vspace{-4pt}' % (title, file_count) + '\n'
	content += r'\begin{minted}{%s}' % lang + '\n'
	content += data
	content += r'\end{minted}' + '\n'


if __name__ == '__main__':
	main()
