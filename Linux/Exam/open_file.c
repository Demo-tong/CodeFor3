/*************************************************************************
	> File Name: open_file.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月29日 星期二 22时05分24秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

main(int argc, char * argv[]){
    int fd_open, fd_open_creat, fd_creat;

    if((fd_open = open("1.txt", O_RDONLY)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("the txt1's descriptor is:%d\n", fd_open);

    unlink("2.txt");
    if((fd_open_creat = open("2.txt", O_CREAT|O_EXCL, 0644)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("the txt2 file descriptor is:%d\n", fd_open_creat);

    if((fd_creat = creat("3.txt", 0644)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("the txt3 file descriptor is:%d\n", fd_creat);

    close(fd_open);
    close(fd_open_creat);
    close(fd_creat);

    return 0;
}
