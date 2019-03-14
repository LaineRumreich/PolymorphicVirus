all: xichigan

xichigan: main.o XtoM.o
	gcc -O1 -Wall -o xichigan main.o XtoM.o -lpthread

main.o: main.c Xichigan.h
	gcc -O1 -Wall -c main.c

XtoM.o: XtoM.c Xichigan.h
	gcc -O1 -Wall -c XtoM.c

clean:
	rm -rf *.o xichigan

