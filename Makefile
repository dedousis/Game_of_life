
default: gameoflife

gameoflife.o: gameoflife.c 
	gcc -g -c -pthread gameoflife.c -o gameoflife.o

gameoflife: gameoflife.o
	gcc gameoflife.o -o gameoflife

clean:
	-rm -f gameoflife.o
	-rm -f gameoflife
