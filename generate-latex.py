import os
import pickle
import subprocess
import sys

MAX_TITLE_LENGTH = 28
MAX_CHARS_PER_LINE = 47
SOURCE_DIR = 'src'
HASHES_CACHE_FILE = 'build/hashes-cache.pickle'
EXCLUDED_FILES = ['.DS_Store']

FILE_WHITELIST = None

def main():
	global hashes_cache

	if os.path.isfile(HASHES_CACHE_FILE):
		with open(HASHES_CACHE_FILE, 'rb') as file:
			hashes_cache = pickle.load(file)
	else:
		hashes_cache = {}

	print(f'% Generated from {SOURCE_DIR} directory.')
	process_dir(SOURCE_DIR)

	with open(HASHES_CACHE_FILE, 'wb') as file:
		pickle.dump(hashes_cache, file, protocol=pickle.HIGHEST_PROTOCOL)

def process_dir(dir_name):
	entries = [os.path.join(dir_name, s) for s in os.listdir(dir_name)]
	entries.sort()

	for entry in entries:
		if not os.path.isdir(entry):
			process_file(entry)

	for entry in entries:
		if os.path.isdir(entry):
			process_dir(entry)

def process_file(path):
	base_name = os.path.basename(path)
	if FILE_WHITELIST is not None and base_name not in FILE_WHITELIST:
		return
	if base_name in EXCLUDED_FILES:
		return

	with open(path, 'r') as file:
		data = file.read()

	if '!!EXCLUDE-FILE' in data:
		return

	title = os.path.relpath(path, SOURCE_DIR)
	sys.stderr.write(f'Processing {title}\n')

	if len(title) > MAX_TITLE_LENGTH:
		sys.stderr.write(f'ERROR: too long title for {title}\n')
		sys.exit(1)

	lines, lines_without_includes = [], []

	for nr, line in enumerate(data.split('\n')):
		if line == '#pragma once':
			continue
		if line.startswith('#include') and 'template.h' in line:
			continue
		if line.startswith('//!') or '//!HIDE' in line:
			continue
		lines.append(line)
		if not line.startswith('#include'):
			lines_without_includes.append(line)
		if len(line.replace('\t', '  ')) > MAX_CHARS_PER_LINE:
			sys.stderr.write(f'ERROR: too long line #{nr+1} in {title}\n')
			sys.exit(1)

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
		data = add_block_hashes(data)
	else:
		lang = 'cpp'
		data = add_block_hashes(data)

	full_hash = get_hash(data_without_includes) if compute_hash else ''

	print('\n\\begin{code}{%s}{%s}{%s}' % (title, lang, full_hash))
	print(data)
	print('\\end{code}')

def add_block_hashes(data, pos=0, is_open=False):
	ret = ''
	while pos < len(data):
		if data[pos] == '{':
			ret += '{'
			tmp, pos = add_block_hashes(data, pos+1, True)
			ret += tmp
		elif is_open and data[pos] == '}':
			block_hash = get_hash(ret)
			ret += '}'
			pos += 1

			while pos < len(data) and data[pos] in ');':
				ret += data[pos]
				pos += 1

			if pos == len(data) or data[pos] == '\n':
				alt = ret + ' // ' + block_hash
				endl = alt.rfind('\n')
				if endl != -1 and len(alt)-endl-1 <= MAX_CHARS_PER_LINE:
					ret = alt
			break
		else:
			ret += data[pos]
			pos += 1
	return (ret, pos) if is_open else ret

def get_hash(data):
	if data in hashes_cache:
		return hashes_cache[data]
	process = subprocess.Popen(['./hash.sh'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, _ = process.communicate(input=data.encode('utf-8'))
	if process.returncode != 0:
		sys.stderr.write(f'ERROR: hashing failed for input:\n' + data + '\n')
		sys.exit(1)
	hashed = stdout.decode('utf-8').strip()
	hashes_cache[data] = hashed
	return hashed

if __name__ == '__main__':
	main()
