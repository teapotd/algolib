import os
import pickle
import subprocess
import sys

MAX_TITLE_LENGTH = 28
MAX_CHARS_PER_LINE = 47
TABLE_OF_CONTENTS = True
HASHES_CACHE_FILE = 'build/hashes-cache.pickle'
EXCLUDED_FILES = ['.DS_Store']

FILE_WHITELIST = None

FILE_TEMPLATE = r'''
\documentclass[10pt]{article}

\usepackage{geometry}
\usepackage{listings}
\usepackage{multicol}
\usepackage{titletoc}
\usepackage{courier}
\usepackage{fancyhdr}
\usepackage{minted}
\usepackage{ulem}
\usepackage{graphicx}

\geometry{
	a4paper,
	landscape,
	includehead,
	hmargin={0.5cm,0.5cm},
	vmargin={0.5cm,0.6cm},
	headsep=0.1cm,
	footskip=0.25cm
}

\setlength{\columnseprule}{0.5pt}
\setlength{\columnsep}{8pt}
\setlength{\parindent}{0pt}

\lstset{basicstyle=\ttfamily\lst@ifdisplaystyle\scriptsize\fi}

\let\underline\relax %% TODO: fixes space length in minted environment, but disables underlines globally - do something smarter

\setminted{tabsize=2}
\setminted{fontsize=\scriptsize}
\setminted{mathescape=true}
\usemintedstyle{tango}

\makeatletter

\let\FV@ListProcessLineOrig\FV@ListProcessLine
\def\FV@ListProcessLine#1{%%
  \ifx\FV@Line\empty
    \hbox{}\vspace{-4pt}%%
  \else
    \FV@ListProcessLineOrig{#1}%%
  \fi}

\newenvironment{code}{%%
	\VerbatimEnvironment
	\let\FV@ListVSpace\relax
	\vspace*{4pt}
	\begin{minted}}
	{\end{minted}}

\makeatother

\pagestyle{fancy}
\fancyhf{}
\renewcommand{\footrulewidth}{0.5pt}
\lhead{Jagiellonian University - Jagiellonian 1}
\rhead{\thepage}

\begin{document}

\begin{multicols*}{4}
%s
\end{multicols*}

\begin{center}
	\includegraphics[scale=1.185]{../appendix.png}
\end{center}

\end{document}
'''

def main():
	global captions, content, hashes_cache
	captions, content = '', ''

	if os.path.isfile(HASHES_CACHE_FILE):
		with open(HASHES_CACHE_FILE, 'rb') as file:
			hashes_cache = pickle.load(file)
	else:
		hashes_cache = {}

	process_dir('src')
	if TABLE_OF_CONTENTS:
		content = captions + '\n\\vspace{\\fill}\\pagebreak\n' + content
	print(FILE_TEMPLATE % content)

	with open(HASHES_CACHE_FILE, 'wb') as file:
		pickle.dump(hashes_cache, file, protocol=pickle.HIGHEST_PROTOCOL)

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
	base_path = os.path.basename(path)
	if FILE_WHITELIST is not None and base_path not in FILE_WHITELIST:
		return
	if os.path.basename(path) in EXCLUDED_FILES:
		return

	with open(path, 'r') as file:
		data = file.read()

	if '!!EXCLUDE-FILE' in data:
		return

	global captions, content
	title = path[path.index('/')+1:]
	sys.stderr.write("Processing %s\n" % title)

	if len(title) > MAX_TITLE_LENGTH:
		sys.stderr.write("WARNING: too long title for %s\n" % title)

	lines, lines_without_includes = [], []

	for nr, line in enumerate(data.split('\n')):
		if line == '#pragma once':
			continue
		if line.startswith('#include ') and 'template.h' in line:
			continue
		if line.startswith('//!') or '//!HIDE' in line:
			continue
		lines.append(line)
		if not line.startswith('#include '):
			lines_without_includes.append(line)
		if len(line) > MAX_CHARS_PER_LINE:
			sys.stderr.write("WARNING: too long line #%d in %s\n" % (nr+1, title))

	data = '\n'.join(lines).strip()
	data_without_includes = '\n'.join(lines_without_includes).strip()
	compute_hash = True

	if path.endswith('.bashrc'):
		lang = 'bash'
		compute_hash = False
	elif path.endswith('.vimrc'):
		lang = 'vim'
		compute_hash = False
	elif path.endswith('.py'):
		lang = 'python'
	elif path.endswith('.java'):
		lang = 'java'
		data, _ = generate_hashes(data, 0, False)
	else:
		lang = 'cpp'
		data, _ = generate_hashes(data, 0, False)

	full_hash = get_code_hash(data_without_includes) if compute_hash else ''

	captions += r'\lstinline|%s|\hfill\pageref{%s}' % (title, title) + '\n\n'

	content += r'\uline{\label{%s}\textbf{\lstinline|%s|}\hfill\lstinline|%s|}' % (title, title, full_hash) + '\n\n'
	content += r'\begin{code}{%s}' % lang + '\n'
	content += data + '\n'
	content += r'\end{code}' + '\n\n'

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
	if data in hashes_cache:
		return hashes_cache[data]
	process = subprocess.Popen(['./hash.sh'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, _ = process.communicate(input=data.encode('utf-8'))
	if process.returncode != 0:
		raise ValueError('Hashing failed')
	hashed = stdout.decode('utf-8').strip()
	hashes_cache[data] = hashed
	return hashed

if __name__ == '__main__':
	main()
