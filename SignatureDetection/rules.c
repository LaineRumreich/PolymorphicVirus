#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int match(char*, char*);
int matchhere(char*, char*);
int matchstar(int, char*, char*);
void codeRed(char *);
void codeYellow();

int main () {
//check name for virus
char *regex, *name;
int check;

codeRed("Virus");
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
	printf("Yay!\n");
}else{
	printf(":(\n");
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
//first delete the file

//tell user virus has been found and deleted
buf = snprintf(buf, 512, "The file %s is a known virus and was found on your computer. It has been deleted.\n", virusName);

MessageBox(0, buf, "Virus Found", 0);
}

