llcp: llcpImp.o Assign05P2.o
	g++ llcpImp.o Assign05P2.o -o a5p2
llcpImp.o: llcpImp.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c llcpImp.cpp
Assign05P2.o: Assign05P2.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign05P2.cpp

go:
	./a5p2
gogo:
	./a5p2 > a5p2test.out

clean:
	@rm -rf llcpImp.o Assign05P2.o
cleanall:
	@rm -rf llcpImp.o Assign05P2.o a5p2
