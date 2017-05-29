#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int n = 0, flag = 0;

char history[100][30];

void hist(int s)
{
	int i, j;
	for(i=0;i<s;i++)
	{
		printf("%d. ", i+1);
		printf("%s",history[i]);
		printf("\n");
	}
}

char** parse(char* command)
{
	int i = 0;
	char** args = (char**)malloc(sizeof(char*)*10);
	char* token;
	const char delim[2] = " ";
	token = strtok(command,delim);
	while(token!=NULL)
	{
		args[i] = (char*)malloc(sizeof(char)*20);
		args[i] = token;
		i++;
		token = strtok(NULL,delim);
	}
	args[i] = token;
	return args;
}

void help()
{
	printf("\nWelcome to the R3V0Shell.\nRun commands like - cd, ls, pwd, sh, history, !, help\n");
	printf("cd changes the directory.\nls lists files and folders in current directory.\n");
	printf("pwd returns present working directory.\nsh opens up linux shell.\n");
	printf("history shows up history of R3V0Shell.\n! executes the command number of history (!1, !2, ...).\n");
	printf("help shows R3V0Shell help\n\n");
}

int execute(char* comd)
{
	pid_t pid, pid_bg;
	if(strcmp(comd,"exit")==0)
		return 0;
	char** args = parse(comd);
	if(strcmp(args[0],"help")==0)
	{
		help();
	}
	if(strcmp(args[0],"cd")==0)
	{
		chdir(args[1]);
	}
	if(strcmp(args[0],"history")==0)
	{
		hist(n);
		return 1;
	} 
	if(args[0][0]=='!')
	{
		int ind = atoi(args[0]+1);
		execute(history[ind-1]);
	}
	pid = fork();
	if(pid==0)
	{
		int stat = execvp(args[0],args);
		if(stat==-1)
			exit(0);
	}
	else
	{
		wait(NULL);
	}
	return 1;
}

int main()
{
	int stat;
	char* prompt="R3v0lut10nist@Alakh";
	char comd[100], *pwd;
	pwd=getcwd(pwd,100);
	while (1)
	{
		pwd=getcwd(pwd,100);
		printf("%s->%s%c ",pwd,prompt,':');
		gets(comd);
		if(strcmp(comd,"")==0)
			continue;
		strcpy(history[n],comd);
		n++;
		stat=execute(comd);
		if(stat==0)
			break;
	}
	return 0;
}