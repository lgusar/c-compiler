# C compiler

Written in C. Compiler based on a book Writing a C compiler by Nora Sandler.

## Build
Build the compiler with `make`.

## Usage
Run the compiler with

`./lgcc file [ --lex | --parse | --codegen ]`
`file` - C source file to compile
`--lex` - end at lexing phase
`--parse` - end at parsing phase
`--codegen` - end at code generation phase

## Tests

Run tests with `make test`.
