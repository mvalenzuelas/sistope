#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char*  argv[])
{

	pid_t pid=getpid();
	int pValue=5;
	int id;


	int** fd=(int**)malloc(sizeof(int*)*pValue);
	for (int i = 0; i < 5; ++i)
	{
		fd[i]=(int*)malloc(sizeof(int)*2);
	}

	for (int i = 0; i < pValue; ++i)
	{
		if (pid)
		{
			pipe(fd[i]);
			pid=fork();
			id=i;
		}
	}
	if (pid)
	{
		waitpid(pid,NULL,0);
		printf("Este es el padre\n");
	}
	if (pid==-1)
	{
		printf("Error al crear al hijo numero\n" );
	}
	if (pid==0)
	{

		char* argv2[argc+2];
		for (int i = 0; i < argc; ++i)
		{
			argv2[i]=argv[i];
		}
		argv2[argc]="-q";
		char stringid[30];
		sprintf(stringid,"%d",id);
		argv2[argc+1]=stringid;
		execv("./out",argv2);
	}
	return 0;
}