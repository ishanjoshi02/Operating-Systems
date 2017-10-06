/*addnum.c systemcall code*/
#include<linux/kernel.h> //kernel.h is used for printk priority level
/*asmlinkage indicates we use the kernel stack to pass parameters */
/*KERN_INFO is one of the 7 priorities,stands for information msgs */
asmlinkage long sys_addnum(int i,int j)
{	
	//print to kernel space
	printk(KERN_INFO "Addnum is working! Now adding %d and %d",i,j);  
	return i+j;					
}
