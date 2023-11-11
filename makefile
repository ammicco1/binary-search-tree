main: main.o bst.o
	gcc -o main main.o bst.o -g

main.o: main.c
	gcc -c main.c -o main.o -g

bst.o: bst.c
	gcc -c bst.c -o bst.o -g

clean:
	rm *.o main