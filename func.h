#define _GNU_SOURCE
#define MAXSEQ 500
#include <unistd.h>


typedef struct task{
	char name[20];
	int arr, exe, pid;
}TASK;

typedef struct seq{
	int taskid, start, exe;
}SEQ;


typedef struct time{
	unsigned long s, ns;
}TIME;


void FIFO(TASK *task, TASK *tmptask, int n);
void RR(TASK *task, TASK *tmptask, int n);
void SJF(TASK *task, TASK *tmptask, int n);
void PSJF(TASK *task, TASK *tmptask, int n);
void RUNSCHEDULER(TASK *task, SEQ *seq, int taskn, int seqn);
void timer(int n);
void yield_to_child(pid_t pid);
