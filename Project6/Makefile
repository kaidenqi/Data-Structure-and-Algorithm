a6: btNode.o Assign06.o
	g++ btNode.o Assign06.o -o a6
btNode.o: btNode.cpp btNode.h
	g++ -Wall -ansi -pedantic -std=c++11 -c btNode.cpp
Assign06.o: Assign06.cpp btNode.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign06.cpp

go:
	./a6
gogo:
	./a6 > a6test.out
nt:
	@rm -rf *.h *.cpp *o *.out a6
clean:
	@rm -rf btNode.o Assign06.o
cleanall:
	@rm -rf btNode.o Assign06.o a6
