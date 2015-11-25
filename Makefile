CFLAGS = -Wall 
CC = gcc

objects = commonSub.o stack.o

genetic: $(objects)
	$(CC) $(CFLAGS) -o commonSub $(objects)

prog5.o: commonSub.c commonSub.h stack.h
stack.o: stack.c stack.h

.PHONY : clean
clean: 
	rm commonSub $(objects)
