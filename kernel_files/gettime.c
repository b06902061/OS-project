#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/ktime.h>

asmlinkage void gettime(unsigned long *s, unsigned long *ns){
	struct timespec time;
	getnstimeofday(&time);
	*s = time.tv_sec;
	*ns = time.tv_nsec;
	return;
}
