#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int cmpRR(const void *a, const void *b){
	return (((TASK *)a)->arr <= ((TASK *)b)->arr) ? -1 : 1;
}

int getRRseq(TASK *task, SEQ *seq, int n){
	int time = 0;
	int done = 0;
	int seqcnt = 0, taskcnt = 0;
	int ready[1000]; //ready queue
	int qf = 0, qb = 0; //queue front, back
	while(done < n){
		//put the arrived process into ready queue
		while(taskcnt < n && task[taskcnt].arr == time){ready[qb++] = taskcnt++;}
		//deal with the process in ready queue, time++ if empty
		if(qf == qb) time++;
		else{
			int id = ready[qf++];
			if(task[id].exe <= 500){
				done += 1;
				seq[seqcnt].taskid = id;
				seq[seqcnt].start = time;
				seq[seqcnt].exe = task[id].exe;
				//check the arrived process during processing
				time += task[id].exe;
				while(taskcnt < n && task[taskcnt].arr <= time){ready[qb++] = taskcnt++;}
			}
			else{
				seq[seqcnt].taskid = id;
				seq[seqcnt].start = time;
				seq[seqcnt].exe = 500;
				task[id].exe -= 500;
				//check the arrived process during processing
				time += 500;
				while(taskcnt < n && task[taskcnt].arr <= time){ready[qb++] = taskcnt++;}
				//put the unfinished process into process
				ready[qb++] = id;
			}
			seqcnt++;
			
		}

	}
	return seqcnt;
}


void RR(TASK *task, TASK *tmptask, int n){
	qsort(task, n, sizeof(TASK), cmpRR);
	qsort(tmptask, n, sizeof(TASK), cmpRR);
	SEQ seq[MAXSEQ];
	int seqcnt = getRRseq(tmptask, seq, n);
	for(int i = 0; i < seqcnt; i++){
		printf("%d %d %d\n", seq[i].taskid, seq[i].start, seq[i].exe);
	}
	RUNSCHEDULER(task, seq, n, seqcnt);	
}
