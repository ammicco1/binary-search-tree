FLAGS = -Wall -ansi -pedantic
OBJS = bst_main.o key.o element.o bst.o
EXEC = bst_main

$(EXEC): $(OBJS)
	gcc $(FLAGS) -o $(EXEC) $(OBJS)

$(EXEC).o: $(EXEC).c
	gcc $(FLAGS) -c $(EXEC).c

bst.o: bst.c
	gcc $(FLAGS) -c bst.c

element.o: element.c
	gcc $(FLAGS) -c element.c

key.o: key.c
	gcc $(FLAGS) -c key.c

clean: 
	rm -f *.o $(EXEC) $(OBJS)