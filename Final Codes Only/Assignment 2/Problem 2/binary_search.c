/*
Name-Ashish Gaurav
Roll-3154029
Batch-A2
*/
#include<stdio.h>
int bs(int [30],int ,int ,int ,int);
int bs(int a[30],int n,int key,int high,int low)
{
	int mid;
	if(low<=high)
	{
		mid=(low+high)/2;
		if(key==a[mid])
		{
			return mid;
		}
		if(key>a[mid])
		{
			return(bs(a,n,key,high,mid+1));
		}
		else
		{
			return(bs(a,n,key,mid-1,low));
		}
	}
	printf("%d is not present\n",key);
	return -1;
}
int main(int argc,char *argv[],char *envp[])
{
	int key,ans;
	int i,x,a[30];
	int n=atoi(argv[1]);
	for(i=0;i<n;i++)
	{
		a[i]=atoi(argv[i+2]);
	}
	printf("Enter the number you want to search\n");
	scanf("%d",&key);
	ans=bs(a,n,key,n-1,0);
	if(ans!=-1)
		printf("Element searched is present\n");
	return 0;
}
