#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int num1 = 0;
static int num2 = 0;
static int num3=0;
static int num4=0;

void func1(int sig)
{
	if (sig == SIGUSR1)
		num1=1;
}

void func2(int sig)
{
	if (sig == SIGUSR2)
		num2=1;
}
int main()
{
	signal(SIGUSR1,func1);
	pid_t pid1 = fork();
	num3=pid1;
	if (pid1==0)
	{
		printf("\nFirst child id=%d sending signal to parent id=%d\n",getpid(),getppid());
		kill(pid1,SIGUSR1);
	}
	else if (pid1>0)
	{
		printf("\nParent process executing with id:%d\n\n",getpid());
		signal(SIGUSR2,func2);
		pid_t pid2 = fork();
		num4=pid2;
		if(pid2==0)
		{
			printf("\nSecond child id=%d sending signal to parent id=%d\n",getpid(),getppid());	
			kill(pid2,SIGUSR2);
		}
		else if(pid2>0)
		{
			while (!num1);
			printf("signal recieved from child number 1 with id:%d.\n",num3);
			while (!num2);
			printf("signal recieved from child number 2 with id:%d.\n",num4);	
		}
	}
	return 0;
}

