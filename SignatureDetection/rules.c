#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main () {
//check name for virus


//check for .exe files


//check file size?


//check encryption?


}

/* Initial code found at https://www.sanfoundry.com/c-program-implement-regular-expression-matching/ 
 * However this code had lots of logic errors in it so I have modified most of it to make it correct
*/
//returns 0 or 1 based on whether the string matched the reg exp given
int regex(char *regexCase, char *strToTest) {
int regLen = 0;
int strLen = 0;
int match = 0;
int same = 0;
//find the length of regexCase and strToTest
for (regLen = 0; regexCase[regLen] != '\0'; regLen++);
for (regLen = 0; regexCase[regLen] != '\0'; regLen++);

if ((regexCase[0] >= 65 && regexCase[0] <= 90) || (regexCase[0] >= 97 && regexCase[0] <=122)) {

	if (regexCase[0] == strToTest[0]) {
		switch (regexCase[1]) {
			case '.' :
			switch (regexCase[2]) {
				case '*':
				if (strLen != 1) {
					if (regexCase[3] == strToTest[strLen-1]) {
						match = 1;
					} else {
						match = 0;
					}
				} else {
					match = 0;
				}
				break;
				case '+':
				if (strToTest[1] != regexCase[3]) {
					if (regexCase[3] == strToTest[strLen - 1]) {
						match = 1;
					} else {
						match = 0;
					}
				}
				break;
				case '?':
				if (strToTest[1] == regexCase[3] || strToTest[2] == regexCase[3]) {
					match = 1;
				} else {
					match = 0;
				}
				break;
			}
			break;
			case '*':
			if (regexCase[regLen-1] == strToTest[strLen-1]) {
				for (i = 0;i <= strLen-2 && same;i++) {
					if(strToTest[i] == regexCase[0]) {
						same = 1;        
					} else {
						same = 0;
					}
				}
				if (same == 1) {
					match = 1;
				} else {
					match = 0;

                                }
			} else {
				match = 0;
			}
			break;
			case '+' :
			if (strLen <= 2) {    
				match = 0;
			}
			else if (regexCase[regLen-1] == strToTest[strLen-1]) {
				for (i = 0;i < tlen-2;i++) {
					if (strToTest[i] == regexCase[0]) {
						same = 1;
					} else {
						same = 0;
					}
				}
				if (same == 1) {
					match = 1;
				} else {
					match = 0;
				}
			}
			break;
			case '?':
			if (regexCase[regLen -1] == strToTest[strLen-1]) {
				match = 1;
			} else {
				match = 0;
			}
			break;
		} 
	} else {
		printf("Does not match");             
	}

        /*

         *If Regular Expression starts with '^'

         */

        else if (regexCase[0] == '^') {
		if (regexCase[1] == strToTest[0]) {
			match = 1;
		} else {
			match = 0;
		}
	}

        /*

         *If Regular Expression Ends with '$'

         */

        else if (regexCase[regLen-1] == '$') {
		if (regexCase[regLen-2] == strToTest[strLen-1]) {
			match = 1;
		} else { 
			match = 0;
		}
	}

}
