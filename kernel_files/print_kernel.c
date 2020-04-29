#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void print_kernel(char *s){
	printk(s);
	return;
}
