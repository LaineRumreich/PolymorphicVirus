#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>

/*
 * Written by Collin Thomas
 *
 * Manages a directory to detect whether files have been modified.
 * Pass directory path and output file via command line.
 */

int check_for_mod(char* path, FILE* fp, char pop_alarm[], FILE* out);
int reprint_file(FILE* fp, int skip_pos, time_t new_time);

char* file_name;

int check_for_mod(char* path, FILE* fp, char pop_alarm[], FILE* out)
{
	char popcheck[3] = "-a";
	int check = 0;
	char temp_path[40];
	long int temp_time;

	struct stat si;

	stat(path, &si);

	int count = 0;

	while(fscanf(fp, "%s\n", temp_path) != EOF)
	{
		if (strcmp(temp_path, path) == 0)
		{
			check = 1;
			fscanf(fp, "%ld\n", &temp_time);
			count++;
			break;
		}
		count++;
	}

	if (check)
	{
		double diff = difftime(temp_time, si.st_mtime);

		char buf1[26];
		char buf2[26];

		struct tm* tm_inf1;
		struct tm* tm_inf2;

		tm_inf1 = localtime(&si.st_mtime);
		tm_inf2 = localtime(&temp_time);

		strftime(buf1, 26, "%Y-%m-%d %H:%M:%S", tm_inf1);
		strftime(buf2, 26, "%Y-%m-%d %H:%M:%S", tm_inf2);
		char msg[1024] = "zenity --error --text \'<span font=\"14\">The following file has been modified: ";
	        strcat(msg, temp_path);
		strcat(msg, "</span>' --title=\"Warning!\" --width=600 --height=150");

		if (diff < 0)
		{
			reprint_file(fp, count, si.st_mtime);
			if (!strcmp(pop_alarm, popcheck))
			{
				system(msg);
			}
		fprintf(out, "%s\t", path);
		fprintf(out, "%s\n", buf1);
		}
	}
	else
	{
		fprintf(fp, "%s\n", path);
		fprintf(fp, "%ld\n", si.st_mtime);
	}

	return 1;
}

int reprint_file(FILE* fp, int skip_pos, time_t new_time)
{
	FILE* t_fp;
	t_fp = fopen("temp.txt", "w");

	char line[1024];
	int count = 0;

	rewind(fp);

	while((fscanf(fp, "%s\n", line) != EOF))
	{
		if (count != skip_pos)
		{
			fprintf(t_fp, "%s\n", line);
	
		}
		else
		{
			fprintf(t_fp, "%ld\n", new_time);
		}
		count++;
	}

	fclose(t_fp);
	remove(file_name);
	rename("temp.txt", file_name);

	return 0;
}

int main(int argc, char* argv[])
{
	while(1)
	{
		DIR* tar_dir;
		struct dirent *entry;

		char* path;
		path = argv[1];

		file_name = argv[2];

		FILE *fp = fopen(file_name, "r+");

		if (fp == NULL)
		{
			fp = fopen(file_name, "w");

			if (fp == NULL)
			{
				printf("Invalid file.\n\n");
				return -1;
			}
		}

		if(!(tar_dir = opendir(argv[1])))
		{
			printf("Invalid directory path.\n\n");
			return -1;
		}

		FILE *out = fopen("detectionLog.txt", "a+");

		while((entry = readdir(tar_dir)) != NULL)
		{
			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			{
				continue;
			}

			if (entry->d_type == DT_REG)
			{
				char file_path[PATH_MAX + 1];
				char full_path[PATH_MAX + 1];
				snprintf(file_path, sizeof(file_path), "%s", entry->d_name);
				snprintf(full_path, sizeof(full_path), "%s", path);
				strcat(full_path, "/");
				strcat(full_path, file_path);
				if (argc == 4)
				{
					int check = check_for_mod(full_path, fp, argv[3], out);	
				}
				else
				{
					int check = check_for_mod(full_path, fp, "NO", out);
				}
			}
		}

		closedir(tar_dir);
		fclose(fp);
		fclose(out);
	}
	return 0;
}
