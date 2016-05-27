#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
void main()
{
	int fd_open,fd_open_creat,fd_creat;
	if((fd_open=open("1.c",O_RDONLY))==-1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("(此文件已存在（只读打开1.c）)\nthe one file's descriptor is:%d\n\n",fd_open);
	char s[20],s1[20];
	printf("（fd_open_creat）请输入文件名(此文件不存在)：");
	scanf("%s",s);
	if((fd_open_creat=open(s,O_CREAT|O_EXCL,0644))==-1)
	{
		perror("open");
                exit(EXIT_FAILURE);
	}
	printf("the two file's descriptor is:%d\n\n",fd_open_creat);
	printf("（fd_creat）请输入文件名(此文件不存在(若存在会清空内容重新创建))：");
	scanf("%s",s1);
	if((fd_creat=creat(s1,0644))==-1)
	{
		perror("creat");
                exit(EXIT_FAILURE);
	}
	printf("the three file's descriptor is:%d\n",fd_creat);
	close(fd_open);
	close(fd_open_creat);
	close(fd_creat);
}


