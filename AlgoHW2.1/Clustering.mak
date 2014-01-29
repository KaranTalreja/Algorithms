CJ: src/Clustering.cpp lex.yy.c OM
	lex src/parser.l
	g++ -O0 -g3 -Wall -o Clustering src/Clustering.cpp obj/om.o -I. 

OM: src/objectModel.cpp include/objectModel.h
	g++ -O0 -g3 -Wall -c src/objectModel.cpp -o obj/om.o -I.


