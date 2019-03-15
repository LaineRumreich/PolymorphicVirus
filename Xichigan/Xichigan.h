#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Threads */
pthread_t *threads;
pthread_attr_t attribute;

/* Function Prototypes */
void XtoM();
//void generateThreads(int x, int index, int* currentThread); 
