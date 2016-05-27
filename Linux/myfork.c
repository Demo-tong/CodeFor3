/*************************************************************************
	> File Name: myfork.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月18日 星期三 21时58分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

struct flock *file_lock(short type,short whence){
        static struct flock fl;
        fl.l_type = type;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_whence = whence;
        fl.l_pid = getpid();
        return &fl;

}

int main(int argc, char **argv){
    int fd;
    pid_t pid;
    char data[1024];

    if(argc == 1)
        return -1;

    if(pid = fork() > 0){
        int read_length = 0;
        while(1){
            sleep(3);
            fd = open(argv[1], O_RDONLY|O_CREAT, 0640);
            fcntl(fd,F_SETLKW,F_WRLCK,SEEK_SET);
            if(fd > 0){
                printf("文件内容为:\n");
                while(read_length = (read(fd, data, sizeof(data)/sizeof(char))) > 0){
                    data[read_length] = '\0';
                    printf("%s", data);
                }
                printf("\n");
            }else{
                perror(argv[1]);
            }
            fcntl(fd,F_SETLKW,file_lock(F_UNLCK,SEEK_SET));
            close(fd);
        }
    }else if(pid == 0){
        int num_write = 0;

        while(1){
            sleep(1);
            fd = open(argv[1],O_WRONLY|O_CREAT|O_APPEND,0640);
            fcntl(fd,F_SETLKW,F_WRLCK,SEEK_SET);
            char str[20];
            sprintf(str," %d",num_write);
            write(fd,str,strlen(str));
            if(fd <= 0){
                perror(argv[1]); 
            }
            
            fcntl(fd,F_SETLKW,file_lock(F_UNLCK,SEEK_SET));
            close(fd);
            num_write++;
        }
    }else if(pid < 0){
        perror(argv[1]);
    }

    return 0;
}
