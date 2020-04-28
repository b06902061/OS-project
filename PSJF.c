#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//sort by increasing arrive time
int cmpPSJFarr(const void *a, const void *b){
	return (((TASK *)a)->arr <= ((TASK *)b)->arr) ? -1 : 1;	
}
//sort by decreasing exe time
int cmpPSJFexe(const void *a, const void *b){
	return (((SEQ *)a)->exe > ((SEQ *)b)->exe) ? -1 : 1;	
}

int getPSJFseq(TASK *task, SEQ *seq, int n){
	int done = 0;
	int time = 0;
	int taskcnt = 0, seqcnt = 0;
	SEQ ready[1000]; int size = 0; //ready list and size
	while(done < n){
		while(taskcnt < n && task[taskcnt].arr == time){
			ready[size++] = (SEQ){taskcnt, 0, task[taskcnt].exe};
			taskcnt++;
		}
		if(size != 0){
			qsort(ready, size, sizeof(SEQ), cmpPSJFexe);
			if(seqcnt != 0 && seq[seqcnt - 1].taskid == ready[size - 1].taskid){ // still the prior process
				ready[size - 1].exe -= 1;
				seq[seqcnt - 1].exe += 1;
			}
			else{ // preempted or the first process
				seq[seqcnt].taskid = ready[size - 1].taskid;
				seq[seqcnt].start = time;
				seq[seqcnt].exe = 1;
				ready[size - 1].exe -= 1;
				seqcnt++;
			}
			// check if the prior process is finished
			if(ready[size - 1].exe == 0){
				done += 1;
				size -= 1;
			}
		}
		time++;
	}
	return seqcnt;
}



void PSJF(TASK *task, TASK *tmptask, int n){
	qsort(task, n, sizeof(TASK), cmpPSJFarr);
	qsort(tmptask, n, sizeof(TASK), cmpPSJFarr);
	SEQ seq[MAXSEQ];
	int seqcnt = getPSJFseq(tmptask, seq, n);
	RUNSCHEDULER(task, seq, n, seqcnt);
}
