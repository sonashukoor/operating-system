#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
	pid_t c1, c2, c3;
	c1 = fork();
	if(c1 == 0)
	{
		sleep(3);
		printf("PID of Child 1 is %d\n", getpid());
		printf("PID of it's parent is %d\n", getppid());
	}
	else //parent
	{
		c2 = fork();
		if(c2 == 0)
		{
			sleep(2);
			printf("PID of Child 2 is %d\n", getpid());
			printf("PID of it's parent is %d\n", getppid());
		}
		else //parent
		{
			c3 = fork();
			if(c3 == 0)
			{
				printf("PID of Child 3 is %d\n", getpid());
				printf("PID of it's parent is %d\n", getppid());
			}
			else //parent
			{
				sleep(4);
				printf("PID of Parent process is %d\n", getpid());
			}
		}
	}
	
}

