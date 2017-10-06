#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int partition(int a[30],int lb,int up,int n);
void quicksort(int a[30],int,int lb,int up);
void display(int a[30],int);
int partition(int a[30],int lb,int up,int n)
{
	int pivot,p,q,temp;
	pivot=lb;
	p=lb+1;
	q=up;
	while(1)
	{
		while(a[pivot]>=a[p]&&p<up)
		{
			p++;
		}
		while(a[pivot]<=a[q]&&q>lb)
		{
			q--;
		}
		if(p<q)
		{
			temp=a[p];
			a[p]=a[q];
			a[q]=temp;
		}
		else
		{
			break;
		}

	}
		temp=a[pivot];
		a[pivot]=a[q];
		a[q]=temp;
	return q;
}
void quicksort(int a[30],int lb,int up,int n)
{
	int i;
	if(lb<=up)
	{
		i=partition(a,lb,up,n);
		quicksort(a,lb,i-1,n);
		quicksort(a,i+1,up,n);
	}
}
void display(int a[30],int n)
{
	int i;
	printf("Sorted elements are:\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");
}
int main()
{
	int a[30],n,i,*status = NULL;
	char *str[100];
	char *ch;
	pid_t pid ;
	printf("Enter the number of elements to search from\n");
	scanf("%d",&n);
	printf("Enter the elements\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	pid = fork();
	quicksort(a,0,n-1,n);
	
	switch(pid)
	{
	case 0:
		asprintf(&ch,"%d",n);
		str[0]="h";
		str[1]=ch;
		for(i=0;i<n;i++)
		{
			asprintf(&ch,"%d",a[i]);
			str[i+2]=ch;
		}
		execve("h",str,NULL);
	break;
	case -1:printf("Error\n");
	break;
	default: 
		 display(a,n);
		 pid = wait(status);
	}
	return 0;
}
