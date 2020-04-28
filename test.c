#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <wait.h>
#include <sys/times.h>
#include <pthread.h>

void set_cpu(int id)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "warning: could not set CPU affinity/n");
    }
}

int main(){
	int x;
	struct sched_param s;
	struct sched_param t;
	s.sched_priority = sched_get_priority_max(SCHED_FIFO) - 3;
	int dd = sched_setscheduler(0, SCHED_FIFO, &s);
	x = fork();
	if(x == 0){
		set_cpu(0x0002);
		for(int i = 0; i < 10; i++){
			puts("---child---");
			printf("%d\n", i);
			if(i % 3 == 1){
				sched_yield();
			}
		}
		exit(0);
	}
	else{
		set_cpu(0x0002);
		for(int i = 0; i < 10; i++){
			puts("---parent---");
			printf("%d\n", i);
			if(i % 3 == 0){
				sched_yield();
			}

		}
		wait(NULL);	
	}
}

