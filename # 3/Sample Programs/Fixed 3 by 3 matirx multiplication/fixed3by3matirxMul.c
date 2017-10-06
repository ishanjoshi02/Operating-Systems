//v3
//Matrix Multiplication
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int a[3][3];
int b[3][3];
int c[3][3];
struct v
{
	int i;
	int j;
};
int sum;
void *result(void *arg);
int main()
{
	pthread_t tid;
	int i,j,k=0;
	void *status=NULL;
	struct v *info=(struct v *)malloc(sizeof(struct v));
	printf("Enter The First Matrix: ");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("Enter at [%d] [%d]\n", i+1, j+1 );
			scanf("%d", &a[i][j]);
		}
	}
	printf("Enter The Second Matrix: ");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{	
			printf("Enter at [%d] [%d]\n", i+1, j+1 );
			scanf("%d", &b[i][j]);
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			info->i=i;
			info->j=j;

			pthread_create(&tid,NULL,result,info);
			pthread_join(tid,&status);
			k=*((int*)status);
			c[info->i][info->j]=k;
		}
	}
	printf("The Matrix Multiplication Is: \n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
}
void *result(void *arg)
{
	struct v *info=arg;
	int p;
	sum=0;
	for(p=0;p<3;p++)
		sum += a[info->i][p]*b[p][info->j];
	pthread_exit(&sum);
}