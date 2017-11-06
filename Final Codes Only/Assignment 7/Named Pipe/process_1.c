/*FIRST PROCESS ACCEPTS MESSAGE FROM USER AND WRITE ON PIPE
PROCESS 2 READS THE MSG AND COUNTS NO. OF WORDS CHAR AND LINES
WRITE THESE CONTENTS TO A NEW FILE
PROCESS 2 WRITES THE CONTENTS TO A NEW PIPE
PROCESS 1 PRINTS THE CONTENTS*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
typedef struct contents
{
 int word,ch,lines;
}con;
void main()
{	con o;
	int fd,fd1,i;
	i=0;
	char str[1024],txt;
	char *f1="fifo";
	char *f2="fifo1";
	mkfifo(f1,0666);
	mkfifo(f2,0666);
	fd=open(f1,O_WRONLY);
	txt=getchar();
	do
	{
		
		str[i]=txt;
		txt=getchar();
		i++;		
		
	}while(txt!='!');

	write(fd,str,sizeof(str));
	close(fd);
	fd1=open(f2,O_RDONLY);
	read(fd1,&o,sizeof(o));
	printf("word:%d\nline:%d\nchar:%d\n",o.word,o.lines,o.ch);
	close(fd1);
	
}
