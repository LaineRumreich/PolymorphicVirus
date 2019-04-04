#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(void) 
{
	size_t len = 0;
	
	const int numFiles = 2;
	char *filenames[numFiles] = { "autorun.inf", "driveicon.ico" };
	
	const int numDrives = 26;
	char *destdrives[numDrives] = {"A:\\", "B:\\", "C:\\", "D:\\", "E:\\",
								"F:\\", "G:\\", "H:\\", "I:\\", "J:\\",
								"K:\\", "L:\\", "M:\\", "N:\\", "O:\\",
								"P:\\", "Q:\\", "R:\\", "S:\\", "T:\\",
								"U:\\", "V:\\", "W:\\", "X:\\", "Y:\\",
								"Z:\\"
	};
	char buffer[BUFSIZ] = { '\0' };
	
	// Copy files to all drives
	
	char src[48];
	char dest[48];
	
	for(int drive = 0; drive < numDrives; drive++)
	{
		for(int file = 0; file < numFiles; file++)
		{
			strcpy(src, filenames[file]);
			
			strcpy(dest, destdrives[drive]);
			strcat(dest, filenames[file]);
			
			FILE *in = fopen(src, "rb");
			FILE *out = fopen(dest, "wb");
			
			if(in == NULL || out == NULL)
			{
				cout << "Error copying " << filenames[file];
				cout << " to drive " << destdrives[drive];
				cout << endl;
				
				in = out = 0;
			}
			else
			{
				while((len = fread(buffer, BUFSIZ, 1, in)) > 0)
				{
					fwrite(buffer, BUFSIZ, 1, out);
				}
				
				cout << "Successfully printed " << filenames[file];
				cout << " to drive " << destdrives[drive];
				cout << endl;
			}
		}
	}
}
