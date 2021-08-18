#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

static int received = 0;

void readUsual(int sig)
{
	 if (sig == SIGUSR1)
	 {
	 	received = 1;
	 }
}

int main()
{ 
	signal(SIGUSR1,readUsual);
	pid_t pid2 = fork(); 
	if (pid2 < 0)
		printf("Can't create child process\n");
	else if (pid2==0)
	{
		printf("Process2, pid=%d\n",getpid());
		while (!received);
	 	printf("SIGUSR1 received.\n");
	}
	else 
	{
	 	kill(pid2,SIGUSR1);
	 	printf("%s\n","Proccess1 end");
	 	while (1);
	}
	return 0;
}

