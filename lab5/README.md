# lex-yacc

## AST

### Description

A program that dumps ast for grammar.

### To run
``` bash
cd building_ast
bison Bison_Rule.y
bison -d Bison_Rule.y -o myapp.cpp
flex -o myapp_lex.cpp test.lex
g++ -o my myapp.cpp myapp_lex.cpp
./my 3.in 0
```

### In a need of compilation, run the makefile using `make -f MAKEFILE` (Linux).
