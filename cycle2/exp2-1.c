#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<sys/types.h>
#include<sys/wait.h>

void prime(int n)
{
	int count = 0, i = 2;
	if(n <= 0)
	{
		printf("Cannot display\n");
		return;
	}
	printf("Prime numbers: ");
	while(count < n)
	{
		int flag = 0;
		for(int j = 2 ; j <= sqrt(i) ; j++)
		{
			if( i % j == 0)
			{
			flag = 1;
			break;
			}
		}
		if(flag != 1)
		{
			printf("%d", i);
			count++;
			if(count < n)
			{
				printf(", ");
			}
		}
		i++;
	}
	printf("\n");
}
void fib(int n)
{
	int a = 0, b = 1, c;
	printf("Fibonacci sequence: ");
	for(int i = 0 ; i < n ; i++)
	{
		printf("%d, ", a);
		c = a + b;
		a = b;
		b = c;
	}
	printf("\n");
}

int main()
{
	int n;
	printf("Enter the limiting value: ");
	scanf("%d", &n);
	
	pid_t id = fork();
	
	if(id < 0)
	{
		printf("Error in process creation\n");
		return 1;
	}
	else if(id == 0) //Child process
	{
	printf("Child process with id %d.\n", getpid());
	printf("Parent id is %d.\n", getppid());
	fib(n);
	}
	else //Parent process
	{
		wait(NULL);
		prime(n);
	}
	
	return 0;
}
