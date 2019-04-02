/*********************************************************
** Tyler Falther										**
** CSE 4471												**
** CalculateHash.c 										**
** 														**
** CalculateHash.c asks the user for input files. It 	**
** then creats a hash value for the file and stores it  **
** in the the file of the users choice.					**
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MtoXEncrypted 1
#define MtoXDecrypted 2

#define EncryptedFilePath "MtoXEncrypted.txt"
#define DecryptedFilePath "MtoXDecrypted.txt"

#define MAXLENGTH 20

void clearInput() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	return;
}

int main() {
	// Get user input
	// Read file
		// Calculate hash as int?
	// write value to end of file

	int currentChoice = 0;
	int cont = 1;

	while (cont) {
		printf("What file are you scanning? \n");
		printf("1. MtoX Encrypted \n");
		printf("2. MtoX Decrypted \n");
		printf("0. Exit \n");
		printf("Enter choice: ");
		scanf ("%d",&currentChoice);
		clearInput();
		printf("\n");

		if (currentChoice != MtoXEncrypted && currentChoice != MtoXDecrypted) {
			cont = 0;
			break;
		}

		int valid = 0;
		char inFileName[MAXLENGTH];
		FILE *inFile;

		while (!valid) {
			printf("Please enter the file name: ");
			fgets(inFileName, MAXLENGTH, stdin);
			fflush(0);

			// clean up input
			int i;
			for(i = 0 ; i < MAXLENGTH ; i++)
     		{
        		if(inFileName[i] == '\n') {
            		inFileName[i] = '\0' ;
        		}
     		}


			inFile = fopen(inFileName, "r+");

			if (inFile == NULL) {
				printf("Invalid file, please try again. \n");
			} else {
				valid = 1;
			}

		}


		FILE *outputFile;

		if (currentChoice == MtoXEncrypted) {
			outputFile = fopen(EncryptedFilePath, "a");

		} else if (currentChoice == MtoXDecrypted) {
			outputFile = fopen(DecryptedFilePath, "a");
		} 
		if (outputFile == NULL) {
			printf("Unable to open output file, ending program. \n");
			return 1;
		}

		int value = 0;
		int ch;
		while ((ch = fgetc(inFile)) != EOF) {
			value += ch;
		}

		fprintf(outputFile, "%d \n", value);

		printf("%s has been  read. \n ", inFileName);
		printf("\n");

		fclose(outputFile);
		fclose(inFile);

	}
	printf("Ending Program \n");

	return 0;
}

