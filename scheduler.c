#include "func.h"
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <wait.h>
#include <sys/times.h>
#include <pthread.h>

struct sched_param high_p, low_p;
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

pid_t create(char *name, int exe){
	pid_t pid = fork();
	if(pid > 0){
		// to open the fifo
		yield_to_child(pid);
		return pid;
	}
	else{
		char exe_t[100];
		sprintf(exe_t, "%d", exe);
		execlp("./task", "./task", name, exe_t, NULL);
	}
}

void yield_to_child(pid_t pid){
	// set the parent and child priority
	if(sched_setscheduler(0, SCHED_FIFO, &low_p) < 0) puts("parent set error.");
	if(sched_setscheduler(pid, SCHED_FIFO, &high_p) < 0) puts("child set error.");
	// yield the priority from parent to child
	sched_yield();
	// must reset the parent priority
	if(sched_setscheduler(0, SCHED_FIFO, &low_p) < 0) puts("parent set error.");
	return;
}

void RUNSCHEDULER(TASK *task, SEQ *seq, int taskn, int seqn){
	set_cpu(0x0001);
	high_p.sched_priority = sched_get_priority_max(SCHED_FIFO);
	low_p.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
	/*
	set the parent_priority = _max - 1, so the child will inherit the priority
	in each iteration, parent set the chosen child_priority = _max and set itself = _max - 1
	and then yield the priority to the chosen child
	*/
	if(sched_setscheduler(0, SCHED_FIFO, &low_p) < 0) puts("parent set error.");


	pid_t child[taskn];
	memset(child, 0, sizeof(pid_t) * taskn);
	mkfifo("fifo", 0666);
	int fifofd;
	int time = 0;
	for(int i = 0; i < seqn; i++){
		if(time < seq[i].start){
			timer(seq[i].start - time);
			time = seq[i].start;
		}
		int taskid = seq[i].taskid;
		if(child[taskid] == 0){ // create child process and open child fifo
			child[taskid] = create(task[taskid].name, task[taskid].exe);
		}
		if(!i) fifofd = open("fifo", O_WRONLY);
		if(write(fifofd, &seq[i].exe, sizeof(int)) < 0) puts("write error.");
		yield_to_child(child[taskid]);
		time += seq[i].exe;
	}
	close(fifofd);
	for(int i = 0; i < taskn; i++){
		waitpid(child[i], NULL, 0);
	}
}
