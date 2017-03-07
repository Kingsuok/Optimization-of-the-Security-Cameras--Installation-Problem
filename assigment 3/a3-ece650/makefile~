all : a3-ece650 a2-ece650 rgen
.PHONY : all
a3-ece650 : driver.o
	cc -o a3-ece650 driver.o
a2-ece650 : assigment2.o input.o BFS.o graph.o
	cc -o a2-ece650 assigment2.o input.o BFS.o graph.o
rgen : rgen.o
	cc -o rgen rgen.o

driver.o : driver.c
	cc -c driver.c 
input.o : format.h 
BFS.o : format.h graph.h 
graph.o : format.h 
assigment2.o : format.h graph.h input.h BFS.h 
rgen.o : rgen.c
	cc -c rgen.c


.PHONY: clean
clean :
	-rm a3-ece650 driver.o a2-ece650 assigment2.o input.o BFS.o graph.o rgen rgen.o

