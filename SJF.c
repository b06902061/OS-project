#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//sort by increasing arrive time
int cmpSJFarr(const void *a, const void *b){
	return (((TASK *)a)->arr <= ((TASK *)b)->arr) ? -1 : 1;	
}
//sort by decreasing exe time
int cmpSJFexe(const void *a, const void *b){
	return (((SEQ *)a)->exe > ((SEQ *)b)->exe) ? -1 : 1;	
}

int getSJFseq(TASK *task, SEQ *seq, int n){
	int done = 0;
	int time = 0;
	int taskcnt = 0, seqcnt = 0;
	SEQ ready[1000]; int size = 0; //ready list and size
	while(done < n){
		while(taskcnt < n && task[taskcnt].arr == time){
			ready[size++] = (SEQ){taskcnt, 0, task[taskcnt].exe};
			taskcnt++;
		}
		if(size == 0) time++;
		else{
			qsort(ready, size, sizeof(SEQ), cmpSJFexe);
			seq[seqcnt] = ready[--size];
			seq[seqcnt].start = time;
			time += seq[seqcnt].exe;
			done += 1;
			seqcnt += 1;
			while(taskcnt < n && task[taskcnt].arr <= time){
				ready[size++] = (SEQ){taskcnt, 0, task[taskcnt].exe};
				taskcnt++;
			}
		}
	}
	return seqcnt;
}



void SJF(TASK *task, TASK *tmptask, int n){
	qsort(task, n, sizeof(TASK), cmpSJFarr);
	qsort(tmptask, n, sizeof(TASK), cmpSJFarr);
	SEQ seq[MAXSEQ];
	int seqcnt = getSJFseq(tmptask, seq, n);
	RUNSCHEDULER(task, seq, n, seqcnt);
}
