#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/syscall.h>
#include <sys/time.h>
#include <fcntl.h>

struct sched_param high_p, low_p;

void yield_to_parent(){
	// set the parent and child priority
	if(sched_setscheduler(getppid(), SCHED_FIFO, &high_p) < 0) puts("child set error.");
	if(sched_setscheduler(0, SCHED_FIFO, &low_p) < 0) puts("parent set error.");
	// yield the priority from parent to child
	sched_yield();
	return;
}

int main(int argc, char **argv){
	printf("%s %d\n", argv[1], getpid());
	fflush(stdout);
	TIME start, end;
	syscall(334, &start.s, &start.ns);
	
	high_p.sched_priority = sched_get_priority_max(SCHED_FIFO);
	low_p.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
	

	int fifofd = open("fifo", O_RDONLY);
	int time = atoi(argv[2]);
	int exe;
	do{
		yield_to_parent();
		if(read(fifofd, &exe, sizeof(int)) < 0){
			puts("read error.");
		}
		time -= exe;
		timer(exe);
	}while(time > 0);
	close(fifofd);
	syscall(334, &end.s, &end.ns);
	char s[300];
	sprintf(s, "[Project1] %d %lu.%09lu\t%lu.%09lu\n", getpid(), start.s, start.ns, end.s, end.ns);
	syscall(333, s);
	if(sched_setscheduler(getppid(), SCHED_FIFO, &high_p) < 0) puts("child set error.");
	exit(0);
}
