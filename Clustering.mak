CJ: src/Clustering.cpp lex.yy.c OM RT
	lex src/parser.l
	g++ -O0 -g3 -Wall -o Clustering src/Clustering.cpp obj/om.o obj/routines.o -I. 

OM: src/objectModel.cpp include/objectModel.h
	g++ -O0 -g3 -Wall -c src/objectModel.cpp -o obj/om.o -I.

RT: src/routines.cpp include/routines.h
	g++ -O0 -g3 -Wall -c src/routines.cpp -o obj/routines.o -I.
