all: xichigan

xichigan: main.o XtoM.o encryptFile.o decryptFile.o
	gcc -O1 -Wall -o xichigan main.o XtoM.o encryptFile.o decryptFile.o -lpthread

main.o: main.c Xichigan.h
	gcc -O1 -Wall -c main.c

XtoM.o: XtoM.c Xichigan.h
	gcc -O1 -Wall -c XtoM.c

encryptFile.o: encryptFile.c Xichigan.h
	gcc -O1 -Wall -c encryptFile.c

decryptFile.o: decryptFile.c Xichigan.h
	gcc -O1 -Wall -c decryptFile.c

clean:
	rm -rf *.o xichigan

