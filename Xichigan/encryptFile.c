#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Functions to encrypt the file XtoM.c											            *
**********************************************************************************/

/*********************************************************************************
Main Function
**********************************************************************************/
void* encryptFile(void* key) {
	int *keyP = (int*)key;
	printf("%i\n", *keyP);

	return NULL;
}
