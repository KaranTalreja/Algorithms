objects = bin/source.o  ../obj/lib/Utils.o
FINAL : bin/exec
	
bin/exec : $(objects)
	g++ -std=c++11 -o bin/exec bin/source.o -L../lib -lUtils
bin/source.o : source/source.cpp
	mkdir -p bin
	g++ -std=c++11 -c source/source.cpp -I../include -o bin/source.o
../obj/lib/Utils.o : ../source/Utils.cpp ../include/Utils.hpp
	mkdir -p ../obj
	mkdir -p ../obj/lib
	mkdir -p ../lib
	g++ -std=c++11 -c -o ../obj/lib/Utils.o ../source/Utils.cpp -I../include
	ar rcs ../lib/libUtils.a ../obj/lib/Utils.o
clean :
	rm -rf $(objects) bin/exec
force : clean FINAL
	
.PHONY: force clean