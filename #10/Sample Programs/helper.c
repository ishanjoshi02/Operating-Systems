#include<stdio.h>
#include<ctype.h>
/*The ctype.h
header file of the C Standard Library declares
several functions that are useful for
testing and mapping characters.*/
#include<syscall.h>
int main()
{
	int var1,var2 =0;
	long res=0;
	printf("Please enter 2 numbers: ");
	scanf("%d%d", &var1, &var2);
	res = syscall(321, var1, var2);
	/* 321 is the line number where we added "<321> COMMON addnum sys_addnum" int the 64-bit
	system call table (syscall_64.tbl)*/
	printf("\nEntered numbers are %d and %d. Addition result is : %ld\n",var1, var2, res);
	return 0;
}
