all: start

start: main.o decryptFile.o morphFile.o
	gcc -o start main.o decryptFile.o morphFile.o

main.o: main.c start.h
	gcc -c main.c

encryptFile.o: decryptFile.c start.h
	gcc -c decryptFile.c

morphFile.o: morphFile.c start.h
	gcc -c morphFile.c

clean:
	rm -rf *.o start

