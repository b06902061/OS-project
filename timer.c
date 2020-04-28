#include "func.h"

void timer(int n){
	for (int i = 0; i < n; i++){
		volatile unsigned long j;
		for(j = 0; j < 1000000UL; j++);
	}
}
