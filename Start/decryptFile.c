#include "start.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Function to decrypt the file xichigan (.o)									            *
**********************************************************************************/

void decryptFile(int key) {
	FILE *xFp;
	char ch;
	int key;

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
}
