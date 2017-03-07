
objects = coverVertex.o input.o satFunction.o 

all : $(objects)
	g++ -o a4-ece650 $(objects) -L. -lsat 

input.o : format.h input.c
	g++ -c input.c
satFunction.o : satFunction.c satFunction.h
	g++ -c satFunction.c
coverVertex.o : coverVertex.c satFunction.h input.h format.h 
	g++ -c coverVertex.c -L. -lsat	
.PHONY: clean
clean :
	-rm a4-ece650 $(objects)
