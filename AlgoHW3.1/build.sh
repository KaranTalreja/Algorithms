#!/bin/bash
# SCRIPT:  method1.sh
# PURPOSE: Process a file line by line with PIPED while-read loop.
echo "Lexer invoked"
lex src/parser.l
echo "running make"
if [ ! -d obj ]; then 
mkdir obj
fi
make -f DynProg.mak CJ
