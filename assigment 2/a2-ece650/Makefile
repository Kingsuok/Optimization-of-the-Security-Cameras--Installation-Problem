
objects = assigment2.o input.o BFS.o graph.o

all : $(objects)
	cc -o a2-ece650 $(objects)
input.o : format.h 
BFS.o : format.h graph.h 
graph.o : format.h 
assigment2.o : format.h graph.h input.h BFS.h 
.PHONY: clean
clean :
	-rm a2-ece650 $(objects)

