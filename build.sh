#!/bin/bash
# SCRIPT:  method1.sh
# PURPOSE: Process a file line by line with PIPED while-read loop.
echo "Lexer invoked"
lex src/parser.l
echo "running make"
make -f Clustering.mak
