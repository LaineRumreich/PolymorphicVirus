all: xichigan

xichigan: main.o MtoX.o encryptFile.o decryptFile.o morphFile.o
	gcc -O1 -Wall -o xichigan main.o MtoX.o encryptFile.o decryptFile.o morphFile.o -lpthread

main.o: main.c Xichigan.h
	gcc -O1 -Wall -c main.c

MtoX.o: MtoX.c Xichigan.h
	gcc -O1 -Wall -c MtoX.c

encryptFile.o: encryptFile.c Xichigan.h
	gcc -O1 -Wall -c encryptFile.c

decryptFile.o: decryptFile.c Xichigan.h
	gcc -O1 -Wall -c decryptFile.c

morphFile.o: morphFile.c Xichigan.h
	gcc -O1 -Wall -c morphFile.c

clean:
	rm -rf *.o xichigan

