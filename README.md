# algolib

C++ competitive programming algorithms notebook.

The library is optimized for ICPC-style competitions, where the code is manually typed from a printed notebook.
In particular, macros are used to shorten the code, sacrificing readability.
The required standard is **C++20**.

You can grab the latest compiled PDF from [workflows](https://github.com/teapotd/algolib/actions).

## Features

### Template and configurations

Typically, at the start of a contest, one person configures the programming environment.

1. [`.vimrc`](src/.vimrc): Vim configuration, including a bind for hash verification.
2. [`.bashrc`](src/.bashrc): Aliases for building and testing. Initially, you may only need `b`, `d` and `run`.
3. [`template.cpp`](src/template.cpp): C++ solution template. It contains macros for code shortening, a debug printer and a stack-trace-on-abort function. Only shortening macros are required by other snippets.

### Debug printer

The template features a `deb` macro for printing debug information. The macro is enabled only if `LOC` is defined, which is the case if the code is compiled using `b` or `d`. Otherwise, everything wrapped in `deb` is **not executed**.

<details>
  <summary>Example usage</summary>

  ```cpp
  struct Elem {
      int k, x;
      pair<int, int> p;
      DBP(k, p); // Make struct printable, output only k and p.
  };

  string foo = "bar";
  vector<Elem> elements = {
      {1, 10, {2, 3}},
      {4, 10, {5, 6}},
      {7, 10, {8, 9}},
  };

  deb(foo, elements);
  ```
  ```
  :: [LINE NUMBER], foo: bar, elements: ((k: 1, p: (2, 3)), (k: 4, p: (5, 6)), (k: 7, p: (8, 9)), )
  ```
</details>

The debug printer supports everything that standard streams can handle, and additionally:

- pairs,
- iterable collections,
- structures marked with the `DBP` macro.

To keep it relatively short, there are a few unsupported edge cases:

1. Commas inside braces within `deb` are not parsed properly.
2. `std::pair` containing `std::vector` cannot be printed. To resolve this, it is enough to wrap the debug printer with `namespace std`.

### Stack-trace on abort

The `template.cpp` triggers segmentation fault in the handler of `SIGABRT` signal. This causes stack-traces to be printed on assertion fails, including those defined by `_GLIBCXX_DEBUG`, when compiled with `d`.

### Hashes for typing correctness

The notebook includes hashes for each snippet and *most* code blocks enclosed by braces `{` and `}`. These hashes are insensitive to white-spaces and C++ comments. The `.vimrc` config binds `_` to hash computation of selected **lines**. To verify if a block enclosed by `{}` has been typed correctly, you can simply place the cursor inside it and use the `vi{_` combination to select the contents and compute the hash.

## Building PDF

1. Install `pdflatex` and `pygments` if not already installed
2. Run `./make.sh`
3. PDF is located in `build` subfolder

## Layout

Due to the 4-column PDF layout, there's a 47-character limit per line with tabs set at 2 spaces, and a 28-character limit for titles. The make script will produce errors if these requirements are violated. Tabs are used for main indentation, while spaces are used for fine alignment. This allows copy-pasting users to set the indentation level to their liking.

## Latex generation

The `generate-latex.py` script creates a single LaTeX file from the source directory `src`. It also generates code hashes. Few directives are supported:

1. Source files containing `!!EXCLUDE-FILE` are excluded.
2. Lines containing `//!HIDE` are skipped.
3. Lines starting with `//!` are skipped. These are used for hidden comments, e.g. marking the source.
4. `#pragma once` and `#include "...template.h"` are also skipped.

## Testing

There are currently three categories of tests in the repository:

1. [own](tests/own): new deterministic tests, fuzz-tests and benchmarks.
2. [yosupo](tests/yosupo): frontends for yosupo's [library-checker](https://github.com/yosupo06/library-checker-problems).
3. [manual](tests/manual): old and dirty "tests", to be removed in the future.

The tests are largely incomplete, especially for older code.
However, all such snippets should be tested in practice unless otherwise specified.

## Licensing

Similar to KACTL, the licensing situation remains unclear.
The notebook is a mix of code authored by the maintainer, and code adapted from various sources to match our style conventions. The source of much of the borrowed code is noted in the comments (hidden in the PDF to save space).
