all: mutationEngine

mutationEngine: main.o decryptFile.o morphFile.o
	gcc -o mutationEngine main.o decryptFile.o morphFile.o

main.o: main.c mutationEngine.h
	gcc -c main.c

encryptFile.o: decryptFile.c mutationEngine.h
	gcc -c decryptFile.c

morphFile.o: morphFile.c mutationEngine.h
	gcc -c morphFile.c

clean:
	rm -rf *.o mutationEngine

