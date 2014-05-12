objects = bin/source.o  ../obj/lib/Utils.o
FINAL : bin/exec
	
bin/exec : $(objects)
	g++ -o bin/exec bin/source.o -L../lib -lUtils -g -Wall
bin/source.o : source/source.cpp ../include/Utils.hpp
	mkdir -p bin
	g++ -c source/source.cpp -I../include -o bin/source.o -g -Wall
../obj/lib/Utils.o : ../source/Utils.cpp ../include/Utils.hpp
	mkdir -p ../obj
	mkdir -p ../obj/lib
	mkdir -p ../lib
	g++ -c -o ../obj/lib/Utils.o ../source/Utils.cpp -I../include -g -Wall
	ar rcs ../lib/libUtils.a ../obj/lib/Utils.o
clean :
	rm -rf $(objects) bin/exec
force : clean FINAL
	
.PHONY: force clean