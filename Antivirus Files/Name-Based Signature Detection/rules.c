#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void checkRules(char*);
int match(char*, char*);
int matchhere(char*, char*);
int matchstar(int, char*, char*);
void codeRed(char[]);
void codeYellow(char[]);

const char PATH[256] = "test";
char IGNORE_THESE_FILES[10][256];
int NUM_FILES_TO_IGNORE;
int CURRENT_SIZE = 10;

int main () {
	// run a continuous loop checking the files in the path for the virus
	while(1) {
		//open directory to check 
		DIR *currDir;
  		struct dirent *dir;
  		currDir = opendir(PATH);
  		if (currDir != NULL) {
  			// read each file
    		while ((dir = readdir(currDir)) != NULL) {
				int check = 1;
    			// calculate the hash for the current file
    			char fullFilePath[100];
    			strcpy(fullFilePath, PATH);
    			strcat(fullFilePath, "/");
    			strcat(fullFilePath, dir->d_name);
      			//check to make sure that file is not to be ignored
				for(int i = 0; i < CURRENT_SIZE; i++) {
					if(strncmp(dir->d_name, IGNORE_THESE_FILES[i], 256) == 0) {
						check = 0;
					}
				}
				if(check) {
					checkRules(dir->d_name);
				}
		    }
    		closedir(currDir);
  		} else {
  			// if the directory cannot be opened, let the user know
  			printf("Unable to open directory: %s \n \n", PATH);
  		}
		//sleep for 10 seconds 
		Sleep(10000);
	}
}


void checkRules(char* name) {
//check name for virus
char *regex;
int check = 0;
//check for .doc, .txt, and .pdf extensions and ignore them 
check = match(".*.doc", name);
if(check) {
	return;
}

check = match(".*.txt", name);
if(check) {
	return;
}

check = match(".*.pdf", name);
if(check) {
	return;
}

check = match(".*.ppt", name);
if(check) {
	return;
}
//First check for files with the name virus in it
check = match("virus", name);
if(check) {
	codeRed(name);
	return;
}

//Next check for files with the name xichigan in it
check = match("xichigan", name);
if(check) {
	codeRed(name);
	return;
}

//Next check for files with the name xichigan in it
check = match("trojan", name);
if(check) {
	codeRed(name);
	return;
}

//Next check for files with the name xichigan in it
check = match("keylogger", name);
if(check) {
	codeRed(name);
	return;
}

//next check the files for the name mutationEngine
check = match("mutationEngine", name);
if(check) {
	codeRed(name);
	return;
}

//next check the files for the name Invader
check = match("Invader", name);
if(check) {
	codeRed(name);
	return;
}

//check for .exe files
check = match(".*.exe", name);
if(check) {
	codeYellow(name);
	return;
}

//check for .o files
check = match(".*.o", name);
if(check) {
	codeYellow(name);
	return;
}

//check for .com files
check = match(".*.com", name);
if(check) {
	codeYellow(name);
	return;
}

//check for common virus names
check = match("Meve", name);
if(check) {
	codeYellow(name);
	return;
}
}

/* Code from https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html */
/* match: search for regexp anywhere in text */
    int match(char *regexp, char *text)
    {
        if (regexp[0] == '^')
            return matchhere(regexp+1, text);
        do {    /* must look even if string is empty */
            if (matchhere(regexp, text))
                return 1;
        } while (*text++ != '\0');
        return 0;
    }

    /* matchhere: search for regexp at beginning of text */
    int matchhere(char *regexp, char *text)
    {
        if (regexp[0] == '\0')
            return 1;
        if (regexp[1] == '*')
            return matchstar(regexp[0], regexp+2, text);
        if (regexp[0] == '$' && regexp[1] == '\0')
            return *text == '\0';
        if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
            return matchhere(regexp+1, text+1);
        return 0;
    }

    /* matchstar: search for c*regexp at beginning of text */
    int matchstar(int c, char *regexp, char *text)
    {
        do {    /* a * matches zero or more instances */
            if (matchhere(regexp, text))
                return 1;
        } while (*text != '\0' && (*text++ == c || c == '.'));
        return 0;
    }

/*Alert the user that a file is a virus and delete that file*/
void codeRed(char virusName[]) {
	char buf[512];
	char fullpath[256];
	int status;
	//get the full path name
	strcpy(fullpath, PATH);
    strcat(fullpath, "/");
    strcat(fullpath, virusName);
	//first delete the file
	status = remove(fullpath);
	//check to see if the file was deleted 
	if(status != 0) {
		//tell the user that the virus could not be deleted
		snprintf(buf, 512, "The file %s is a known virus, however an error was encountered when trying to delete the file.\n", virusName);
		MessageBox(0, buf, "Error Deleting", 0);
	} else {
		//tell user virus has been found and deleted
		snprintf(buf, 512, "The file %s is a known virus and was found on your computer. It has been deleted.\n", virusName);
		MessageBox(0, buf, "Virus Found", 0);
	}
}

void codeYellow(char virusName[]) {
	char buf[512];
	char fullpath[256];
	int status;
	int choice;
	
	//alert the user of a suspicious file and ask them if they want to delete it 
	snprintf(buf, 512, "The file %s is suspicious. Would you like to delete it?\n", virusName);
	choice = MessageBox(0, buf, "Possible Virus", MB_YESNO);
	//check to see if the user said no
	if(choice == 7) {
		NUM_FILES_TO_IGNORE++;
		//check to see if the array needs to be increased
		if(NUM_FILES_TO_IGNORE > CURRENT_SIZE - 1) {
			char temp[CURRENT_SIZE][256];
			for(int i = 0; i < CURRENT_SIZE; i++) {
				strcpy(temp[i], IGNORE_THESE_FILES[i]);
			}
			char IGNORE_THESE_FILES[CURRENT_SIZE * 2][256];
			//add filenames back to the array
			for(int i = 0; i < CURRENT_SIZE; i++) {
				strcpy(IGNORE_THESE_FILES[i], temp[i]);
			}
			strcpy(IGNORE_THESE_FILES[NUM_FILES_TO_IGNORE], virusName);
			CURRENT_SIZE *= 2;
		} else {
			strcpy(IGNORE_THESE_FILES[NUM_FILES_TO_IGNORE], virusName);
		}
	} else {
		//get the full path name
		strcpy(fullpath, PATH);
		strcat(fullpath, "/");
		strcat(fullpath, virusName);
		//first delete the file
		status = remove(fullpath);
		//check to see if the file was deleted 
		if(status != 0) {
			//tell the user that the virus could not be deleted
			snprintf(buf, 512, "The file %s that you asked to be deleted could not be deleted\n", virusName);
			MessageBox(0, buf, "Error Deleting", 0);
		} else {
			//tell user virus has been found and deleted
			snprintf(buf, 512, "The file %s has been deleted.\n", virusName);
			MessageBox(0, buf, "Virus Found", 0);
		}
	}
}