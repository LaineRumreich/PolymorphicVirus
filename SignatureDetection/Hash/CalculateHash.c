/*********************************************************
** Tyler Falther										**
** CSE 4471												**
** CalculateHash.c 										**
** 														**
** CalculateHash.c asks the user for input files. It 	**
** then creats a hash value for the file and stores it  **
** in the the file of the users choice.					**
********************************************************/

// Needed libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the files that can be read
#define MtoXEncrypted 1
#define MtoXDecrypted 2

// Paths for all hashes for each file to be read
#define EncryptedFilePath "MtoXEncrypted.txt"
#define DecryptedFilePath "MtoXDecrypted.txt"

// Max file name length
#define MAXLENGTH 20

// to clear input from scanf
void clearInput() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	return;
}

int main() {

	// set up current choice and loop
	int currentChoice = 0;
	int cont = 1;

	// run until user exits
	while (cont) {
		// Get type of file
		printf("What file are you scanning? \n");
		printf("1. MtoX Encrypted \n");
		printf("2. MtoX Decrypted \n");
		printf("0. Exit \n");
		printf("Enter choice: ");
		scanf ("%d",&currentChoice);
		clearInput();
		printf("\n");

		// break if a valid file isn't entered
		if (currentChoice != MtoXEncrypted && currentChoice != MtoXDecrypted) {
			cont = 0;
			break;
		}

		// Get the file to be calculated
		int valid = 0;
		char inFileName[MAXLENGTH];
		FILE *inFile;

		// Run until a valid file is entered 
		while (!valid) {
			// get file name
			printf("Please enter the file name: ");
			fgets(inFileName, MAXLENGTH, stdin);
			fflush(0);

			// clean up file name
			int i;
			for(i = 0 ; i < MAXLENGTH ; i++)
     		{
        		if(inFileName[i] == '\n') {
            		inFileName[i] = '\0' ;
        		}
     		}

     		// try to open file
			inFile = fopen(inFileName, "r+");

			// if file cannot be opend, ask the user to try again
			if (inFile == NULL) {
				printf("Invalid file, please try again. \n");
			} else {
				valid = 1;
			}

		}


		// Get the hash file to appened to
		FILE *outputFile;
		if (currentChoice == MtoXEncrypted) {
			outputFile = fopen(EncryptedFilePath, "a");

		} else if (currentChoice == MtoXDecrypted) {
			outputFile = fopen(DecryptedFilePath, "a");
		} 
		// if hash file cannot be opend, end program
		if (outputFile == NULL) {
			printf("Unable to open output file, ending program. \n");
			return 1;
		}

		// calculate hash - just a sum of all characters 
		// can probably make this more sophisticated if needed
		int value = 0;
		int ch;
		while ((ch = fgetc(inFile)) != EOF) {
			value += ch;
		}

		// print the hash value to the output file
		fprintf(outputFile, "%d \n", value);

		printf("%s has been  read. \n ", inFileName);
		printf("\n");

		// close files 
		fclose(outputFile);
		fclose(inFile);

	}
	printf("Ending Program \n");

	return 0;
}

