#include <stdio.h>
#include "func.h"

int main(){
	int n;
	char policy[10];
	scanf("%s%d", policy, &n);
	TASK task[n], tmptask[n];
	for(int i = 0; i < n; i++){
		scanf("%s%d%d", task[i].name, &task[i].arr, &task[i].exe);
		tmptask[i] = task[i];
	}
	if(policy[0] == 'F') FIFO(task, tmptask, n);
	else if(policy[0] == 'R') RR(task, tmptask, n);
	else if(policy[0] == 'S') SJF(task, tmptask, n);
	else if(policy[0] == 'P') PSJF(task, tmptask, n);
}
