#include<dirent.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>

pid_t checkproc(char* dir)
{
	DIR* proc_dir;
	DIR* ind_proc;

	struct dirent *entry;
	struct dirent *pid_entry;

	if(!(proc_dir = opendir(dir)))
	{
		return -1;
	}

	while(entry = readdir(proc_dir))
	{
		if (entry->d_type == 4)
		{
			char path[2048];
			snprintf(path, sizeof(path), "%s", entry->d_name);
			/*char* pid_dir = dir;
			strcat(pid_dir, "/");
			strcat(pid_dir, path);
			printf("subdir: %s\n", pid_dir);
			if(!(ind_proc = opendir(pid_dir)))
			{
				return -1;
			}*/	
			printf("proc: %s, type: %d, path: %s\n", entry->d_name, entry->d_type, path);
		}
	}
	
	closedir(proc_dir);

	return 1;
}

int kill_proc(pid_t pid)
{
	char ans;
	printf("Enter 'y' if you would like to kill this process: ");
	scanf("%c", &ans);

	if(ans == 'y')
	{
		//kill(pid, SIGKILL);
		return 1;
	}

	return -1;
}

int main()
{
	pid_t pid;
	char dir[] = "/proc";
	
	pid = checkproc(dir);

	if(kill_proc(pid) == 1)
	{
		printf("Process killed successfully...");
	}
	else
	{
		printf("Error: process not killed...");
	}

	printf("Opened: %d\n", 1);
	return 0;
}
