/********************************************************************
	> File Name: connect_fork.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月19日 星期四 13时32分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char** argv){
    int i, n, fd;
    pid_t pid;
    char *output;

    if(argc != 2){
        printf("The parameter is not correct!\n");
        return -1;
    }
    
    i = 0;
    if((fd = open(argv[1], O_RDWR|O_CREAT)) == -1){
        perror("open");
        exit(-1);
    }

    if(pid = fork()){//父进程休眠3秒，读出文件内的信息并显示
        while(1){
            sleep(3);

            int num_length = lseek(fd, 0, SEEK_END);
            output = (char *)malloc(num_length);

            lseek(fd, 0, SEEK_SET);

            if((n = read(fd, output, num_length)) == -1){
                perror("read");
                exit(-1);
            }

            output[n] = '\0';
            printf("The dictionary is:%s\n", output);
        }
    }

    else{//子进程，休眠1秒将内容写到文件中
         while(1){
            sleep(1);
            char input[4] = "ABC";
            
             if(write(fd, input, strlen(input)) == -1){
                perror("write");
                exit(-1);
            }
            printf("writing!\n");
        }
    }

    return 0;
}
