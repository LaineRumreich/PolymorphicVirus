all: start

xichigan: main.o encryptFile.o decrpytFile.o morphFile.o
	gcc -o xichigan main.o encryptFile.o decrpytFile.o morphFile.o

main.o: main.c start.h
	gcc -c main.c

encryptFile.o: encryptFile.c start.h
	gcc -c encryptFile.c

morphFile.o: morphFile.c start.h
	gcc -c morphFile.c

clean:
	rm -rf *.o start

