#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int cmpFIFO(const void *a, const void *b){
	return (((TASK *)a)->arr <= ((TASK *)b)->arr) ? -1 : 1;
}

int getFIFOseq(TASK *task, SEQ *seq, int n){
	int time = 0;
	for(int i = 0; i < n; i++){
		if(time <= task[i].arr){
			seq[i].start = task[i].arr;
			seq[i].exe = task[i].exe;
			seq[i].taskid = i;
			time = task[i].arr + task[i].exe;
		}
		else{
			seq[i].start = time;
			seq[i].exe = task[i].exe;
			seq[i].taskid = i;
			time += task[i].exe;
		}
	}
	return n;
}

void FIFO(TASK *task, TASK *tmptask, int n){
	qsort(task, n, sizeof(TASK), cmpFIFO);
	qsort(tmptask, n, sizeof(TASK), cmpFIFO);
	SEQ seq[MAXSEQ];
	int seqcnt = getFIFOseq(tmptask, seq, n);
	RUNSCHEDULER(task, seq, n, seqcnt);
}
