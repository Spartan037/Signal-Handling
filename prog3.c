#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

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
	 if (pid1 < 0)
	 	printf("Can't create child process\n");
	 else if (pid1==0)
	 	printf("\nChild process executing with id:%d\n\n",getpid());
	 else if(pid1>0)
	 {
	 	printf("\n parent process id=%d sending signal to child id=%d\n",getpid(),getppid());
		kill(pid1,SIGUSR1);
		signal(SIGUSR2,func2);
		pid_t pid2 = fork();
		num4=pid2;
		if(pid2==0)
		{
			printf("\nSecound child id=%d  id=%d\n",getpid(),getppid());
			while (!num1 && !num2);
			printf("signal recieved from parent  with id:%d.\n",num3);			
		}
		else if(pid2>0)
		{
			printf("\n parent process id=%d sending signal to child2 id=%d\n",getpid(),getppid());	
			kill(pid2,SIGUSR2);
		}
		while (1);
	 }
	 return 0;
}

