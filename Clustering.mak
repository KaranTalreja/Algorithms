CJ: src/Clustering.cpp lex.yy.c
	lex src/parser.l
	g++ -O0 -g3 -Wall -o Clustering src/Clustering.cpp -I.
