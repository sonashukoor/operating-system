#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void main()
{
	pid_t a,b,c,d,e,f,g,h,i;
	printf("PID of A is %d\n", getpid());
	b = fork();
	if(b == 0){
		printf("PID of B is %d\n", getpid());
		printf("PID of Parent is %d\n", getppid());
		d = fork();
		if(d == 0){
			printf("PID of D is %d\n", getpid());
			printf("PID of Parent is %d\n", getppid());
			h = fork();
			if(h == 0){
				printf("PID of H is %d\n", getpid());
				printf("PID of Parent is %d\n", getppid());
				i = fork();
				if(i == 0){
					printf("PID of I is %d\n", getpid());
					printf("PID of Parent is %d\n", getppid());
				}
				else{
					wait(NULL); //h wait for i
				}
			}
			else{
				wait(NULL); //d wait for h
			}
		}
		else{
			wait(NULL); //b wait for d
			e = fork();
			if(e == 0){
				printf("PID of E is %d\n", getpid());
				printf("PID of Parent is %d\n", getppid());
			}
			else{
				wait(NULL); //b wait for e
				f = fork();
				if(f == 0){
					printf("PID of F is %d\n", getpid());
					printf("PID of Parent is %d\n", getppid());
				}
				else{
					wait(NULL); //b wait for f
					
				}
			}
		}
	}
	else{
		wait(NULL); //a wait for b
		c = fork();
		if(c == 0){
			printf("PID of C is %d\n", getpid());
			printf("PID of Parent is %d\n", getppid());
			g = fork();
			if(g == 0){
				printf("PID of G is %d\n", getpid());
				printf("PID of Parent is %d\n", getppid());
			}
			else{
				wait(NULL);// c parent wait for g child
			}
		}
		else{
			wait(NULL); //a parent wait for c child
		}
	}
}
