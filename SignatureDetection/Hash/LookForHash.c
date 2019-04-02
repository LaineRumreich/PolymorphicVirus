#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EncryptedFilePath "MtoXEncrypted.txt"
#define DecryptedFilePath "MtoXDecrypted.txt"
#define PATHS "Paths.txt"

// Cleans up any junk that may have been added to the file. This might have to be
// integrated in with just scanning it (stop the scan at a certain pont)
void cleanJunk() {

}

int main() {

	printf("Starting Program... \n");

	FILE *paths;
	paths = fopen(PATHS, "r");

	if (paths == NULL) {
		printf("Error reading Paths.txt. Ending program \n");
		return 1;
	}

	int numPaths = 0;

	int ch;
	while((ch = fgetc(paths)) != EOF) {
		if (ch == '\n') {
			numPaths++;
		}
	}
	print("%d", numPaths);

	rewind(paths);

	char *paths[numPaths];

	// Get list of directories to check - from a file

	// For each directory

		// Search for MtoX signature - Encrypted

		// Search for MtoX signature - Decrypted

		// Search for Start file signature? 


	return 0;
}
