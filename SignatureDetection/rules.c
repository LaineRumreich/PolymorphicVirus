#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int checkRules(char*);
int match(char*, char*);
int matchhere(char*, char*);
int matchstar(int, char*, char*);
void codeRed(char *);
void codeYellow(char *);

const char PATH;
char IGNORE_THESE_FILES[10];
int NUM_FILES_TO_IGNORE;
int CURRENT_SIZE;

int main () {
	
}


int checkRules(char* name) {
//check name for virus
char *regex;
int check;

codeYellow("Virus");
//First check for files with the name virus in it
check = match("virus", "virus");
if(check) {
	printf("Yay!\n");
}else{
	printf(":(\n");
}

//Next check for files with the name xichigan in it
check = match("xichigan", name);
if(check) {
	codeRed(name);
}
//check for .exe files


//check file size?


//check encryption?


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
void codeRed(char *virusName) {
	char buf[512];
	char* fullpath;
	int status;
	//get the full path name
	fullpath = PATH + virusName;
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

void codeYellow(char* virusName) {
	char buf[512];
	char* fullpath;
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
			char temp[CURRENT_SIZE] = IGNORE_THESE_FILES;
			char IGNORE_THESE_FILES[CURRENT_SIZE * 2];
			//add filenames back to the array
			for(int i = 0; i < CURRENT_SIZE; i++) {
				IGNORE_THESE_FILES[i] = temp[i];
			}
			IGNORE_THESE_FILES[NUM_FILES_TO_IGNORE] = virusName;
			CURRENT_SIZE *= 2;
		} else {
			IGNORE_THESE_FILES[NUM_FILES_TO_IGNORE] = virusName;
		}
	} else {
		//get the full path name
		fullpath = PATH + virusName;
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