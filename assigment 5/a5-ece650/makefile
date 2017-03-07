
objects = VC0.o VC1.o VC2.o input.o satFunction.o main.o

all : $(objects)
	g++ -o a5-ece650 $(objects) -L. -lsat -lpthread 
main.o : main.cpp VC0.h VC1.h VC2.h input.h
	g++ -c main.cpp 
input.o : format.h input.cpp
	g++ -c input.cpp
satFunction.o : satFunction.cpp 
	g++ -c satFunction.cpp
VC0.o : VC0.cpp satFunction.h format.h 
	g++ -c VC0.cpp 	
VC1.O : VC1.cpp format.h
	g++ -c VC1.cpp
VC2.O : VC2.cpp format.h
	g++ -c VC2.cpp
.PHONY: clean
clean :
	-rm a5-ece650 $(objects)
