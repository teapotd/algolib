import os
import subprocess
import sys

MAX_CHARS_PER_LINE = 47

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
\lstset{basicstyle=\ttfamily\lst@ifdisplaystyle\scriptsize\fi}

\setminted{tabsize=2}
\setminted{fontsize=\scriptsize}
\usemintedstyle{tango}

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

	global captions, content, file_count
	title = path[path.index('/')+1:]
	file_count += 1
	sys.stderr.write("Processing %s\n" % title)

	lines, lines_without_includes = [], []

	for line in data.split('\n'):
		if line == '#pragma once':
			continue
		if line.startswith('#include ') and 'template.h' in line:
			continue
		if line.startswith('//!'):
			continue
		lines.append(line)
		if not line.startswith('#include '):
			lines_without_includes.append(line)

	data, _ = generate_hashes('\n'.join(lines).strip(), 0, False)
	full_hash = get_code_hash('\n'.join(lines_without_includes).strip())

	lang = 'cpp'
	if path.endswith('.bashrc'):
		lang = 'bash'
	elif path.endswith('.vimrc'):
		lang = 'vim'

	captions += r'\noindent{\lstinline|%s|}\hfill\pageref{%s}\break' % (title, title) + '\n'

	content += r'\noindent{\uline{\textbf{\lstinline|%s|}\hfill\lstinline|%s|}}\vspace{-4pt}' % (title, full_hash) + '\n'
	content += r'\label{%s}' % title + '\n'
	content += r'\begin{minted}{%s}' % lang + '\n'
	content += data + '\n'
	content += r'\end{minted}' + '\n'

def generate_hashes(data, pos, is_open):
	ret = ''
	while pos < len(data):
		if data[pos] == '{':
			ret += '{'
			tmp, pos = generate_hashes(data, pos+1, True)
			ret += tmp
		elif is_open and data[pos] == '}':
			code_hash = get_code_hash(ret)
			ret += '}'
			pos += 1

			if pos < len(data) and data[pos] == ')':
				ret += ')'
				pos += 1

			if pos < len(data) and data[pos] == ';':
				ret += ';'
				pos += 1

			if pos == len(data) or data[pos] == '\n':
				alt = ret + ' // ' + code_hash
				endl = alt.rfind('\n')
				if endl != -1 and len(alt)-endl-1 <= MAX_CHARS_PER_LINE:
					ret = alt
			break
		else:
			ret += data[pos]
			pos += 1
	return ret, pos

def get_code_hash(data):
	process = subprocess.Popen(['./hash.sh'],
		stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, _ = process.communicate(input=data.encode("utf-8"))
	return stdout.decode('utf-8').strip()

if __name__ == '__main__':
	main()
