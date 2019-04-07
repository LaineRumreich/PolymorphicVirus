/*********************************************************
** Tyler Falther										**
** CSE 4471												**
** LookForHash.c										**
** 														**
** LookForHash.c looks for files that have a hash value **
** that matches one from a know viruse file. First, it  **
** gets a list of directories to check from Paths.txt.  **
** After that, it will look at each file in every path  **
** and calculate a hash. If its hash matches that of  	**
** a known virus file, it alerts the user.				**
********************************************************/

// Needed libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

// Paths and max path length
#define EncryptedFilePath "MtoXEncrypted.txt"
#define DecryptedFilePath "MtoXDecrypted.txt"
#define PATHS "Paths.txt"
#define MAXLENGTH 100

// Cleans up any junk that may have been added to the file. This might have to be
// integrated in with just scanning it (stop the scan at a certain pont)
void cleanJunk() {

}

// Calculates the hash value for the given file
int calculateHash(char *fileName) {

	// Try to open the file
	FILE *calcFile = fopen(fileName, "r");

	// If the file cannot be opened, let the user know.
	if (calcFile == NULL) {
		printf("Unable to open %s \n", fileName);
		return 0;
	}

	int value = 0;
	int ch;

	// read each character in the file and add its value to the result
	while ((ch = fgetc(calcFile)) != EOF) {
		value += ch;
	}

	// close file and return total value
	fclose(calcFile);
	return value;
}

// For a given hash value, check to see if ther is a matching value in the give file
int checkForMatch(int hash, char *hashFile) {

	// Open file
	FILE *file = fopen(hashFile, "r");
	// Let user know if file could not be opened
	if (file == NULL) {
		printf("Unable to open %s \n", hashFile);
	}

	int result = 0;
	int nextValue = 0;

	// Look at every value in the file
	fscanf (file, "%d", &nextValue); 
	while (!feof(file)) {
		// If a value is found the matches the hash, set result to 1 and end the search
		if (nextValue == hash) {
			result = 1;
			break;
		} else {
			// check next value if there isn't a match
			fscanf (file, "%d", &nextValue); 
		}
	}

	// close file and return the result
	fclose(file);
	return result;
}

// main function
int main() {

	printf("Starting Program... \n \n");

	// Get file paths to check
	FILE *pathsFile;
	pathsFile = fopen(PATHS, "r");

	// If file with the paths could not be opened, end program
	if (pathsFile == NULL) {
		printf("Error reading Paths.txt. Ending program \n");
		return 1;
	}

	int numPaths = 0;

	// Calculate the number of paths that are in the file
	int ch;
	while((ch = fgetc(pathsFile)) != EOF) {
		if (ch == '\n') {
			numPaths++;
		}
	}

	// rewind back to start
	rewind(pathsFile);

	// array to hold all of the paths
	char paths[numPaths][MAXLENGTH];

	char * line = NULL;
	size_t length = 0;
	ssize_t next;
	int count = 0;

	// read each line if the file - there is one path per line
	while((next = getline(&line, &length, pathsFile)) != -1) {

		int i;
		// clean off newline characters at the end
		for(i = 0 ; i < length ; i++)
     	{
        	if(line[i] == '\n') {
            	line[i] = '\0' ;
        	}
     	}

     	// add path to array
		strcpy(paths[count], line);
		count++;
	}

	fclose(pathsFile);

	// run a loop checking each path for the virus
	int index = 0;
	while(index < numPaths) {

		// Get the current path to check
		char currentPath[100];
		strcpy(currentPath, paths[index]);

		// open the direectory
		DIR *currentD;
  		struct dirent *dir;
  		currentD = opendir(currentPath);
  		if (currentD != NULL) {
  			// If the directory can be opened, read each file in it
  			printf("Checking Directory: %s \n \n", currentPath);
  			// read each file
    		while ((dir = readdir(currentD)) != NULL) {
    			// calculate the hash for the current file
    			char fullFilePath[100];
    			strcpy(fullFilePath, currentPath);
    			strcat(fullFilePath, "/");
    			strcat(fullFilePath, dir->d_name);
      			int check = calculateHash(fullFilePath);

      			// check if hash matches a known virus 
				int decrypt = checkForMatch(check, DecryptedFilePath);
				int encrypt = checkForMatch(check, EncryptedFilePath);

				// if there is a match, let the user know
				if (decrypt || encrypt) {
					printf("WARNING: Detected Possible Virus! \n");
					printf("SUSPECT FILE: %s \n", dir->d_name);
					printf("If you do not recognize this file, please delete it! \n");
					getchar();
				}

		    }
    		closedir(currentD);
  		} else {
  			// if the directory cannot be opened, let the user know
  			printf("Unable to open directory: %s \n \n", currentPath);
  		}


  		// check next path
		index++;
		// reest back to begining of the paths array
		if (index == numPaths) {
			index = 0;
		}

	}

	return 0;
}
