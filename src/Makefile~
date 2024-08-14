# Build targets
# lm - link math library library. required if you use math.h functions (commonly
# linked by default on mac).
problem2a: problem2a.o utils.o graph.o pq.o list.o
	gcc -Wall -o problem2a -g -lm problem2a.o utils.o graph.o pq.o list.o

problem2c: problem2c.o utils.o graph.o pq.o list.o
	gcc -Wall -o problem2c -g -lm problem2c.o utils.o graph.o pq.o list.o

problem3: problem3.o
	gcc -Wall -o problem3 -g -lm problem3.o


problem2a.o: problem2a.c graph.h utils.h
	gcc -c problem2a.c -Wall -g

problem2c.o: problem2c.c graph.h utils.h
	gcc -c problem2c.c -Wall -g

problem3.o: problem3.c
	gcc -c problem3.c -Wall -g

utils.o: utils.c utils.h graph.h
	gcc -c utils.c -Wall -g

graph.o: graph.c graph.h pq.h utils.h
	gcc -c graph.c -Wall -g

pq.o: pq.c pq.h
	gcc -c pq.c -Wall -g

list.o: list.c list.h
	gcc -c list.c -Wall -g
