#include "Xichigan.h"

/*********************************************************************************
* Author: Laine Rumreich								       				 				   *
*																				 							*
*																				 							*
* Called from: main.c										 					 					*
*																				 							*
* Function to search for text (including Microsoft Office) files on the desktop  *
* of the current user, opens them, and replaces every ‘M’ or ‘m’ with ‘X’        *
**********************************************************************************/

void XtoM() {
	 DIR *d;
    struct dirent *dir;
    d = opendir("..\\Desktop");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

}
