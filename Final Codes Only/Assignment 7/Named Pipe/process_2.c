#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#define max 1024
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>
typedef struct contents
{
 int word,ch,lines;
}con;
void main()
{
	int fd,fd1,i,no;
	con o;
	o.word=1;
	o.ch=0;
	o.lines=1;
	FILE *fp;
	char buff[max];
	char *f1="fifo";
	char *f2="fifo1";
	mkfifo(f1,0666);
	mkfifo(f2,0666);
	fd=open(f1,O_RDONLY);
	read(fd,buff,max);
	no=strlen(buff);
	for(i=0;i<no;i++)
	{
		if(isalnum(buff[i]))
		{
			o.ch++;
		}
		else if(buff[i]=='\n')
		{
			o.lines++;
		}
		else if(buff[i]==' ')
		{
			o.word++;
		}
		else
		{
		}
		
	}
	fp=fopen("PROCESS.txt","w");
	fwrite(&o,sizeof(o),1,fp);
	fread(&o,sizeof(o),1,fp);
	close(fd);
	fd1=open(f2,O_WRONLY);
	write(fd1,&o,sizeof(o));
	close(fd1);
}
