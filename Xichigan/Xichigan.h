#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>


/* Function Prototypes */
void MtoX();
void encryptFile(int key);
void decryptFile(int key); 
