all: xichigan

xichigan: main.o XtoM.o encryptFile.o
	gcc -O1 -Wall -o xichigan main.o XtoM.o encryptFile.o -lpthread

main.o: main.c Xichigan.h
	gcc -O1 -Wall -c main.c

XtoM.o: XtoM.c Xichigan.h
	gcc -O1 -Wall -c XtoM.c

encryptFile.o: encryptFile.c Xichigan.h
	gcc -O1 -Wall -c encryptFile.c

clean:
	rm -rf *.o xichigan

