#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
        int fd;
        char buffer[BUFFER_SIZE];
        if(argc != 2){
                fprintf(stderr, "Usages:%s ouffilename!\n\a", argv[0]);
                exit(EXIT_FAILURE);
        }
        if((fd=open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)) == -1){
                fprintf(stderr, "Open %s Error:%s\n\a", argv[1],strerror(errno));
                exit(EXIT_FAILURE);
        }
        if(dup2(fd, fileno(stdout)) == -1){
                fprintf(stderr, "Redirect standard Out Error:%s\n\a", strerror(errno));
                exit(EXIT_FAILURE);
        }
        fprintf(stderr, "Now ,please input string");
        fprintf(stderr, "(To quit use CTRL+C)\n");
        while(1){
                fgets(buffer, BUFFER_SIZE, stdin);
                if(feof(stdin))
                        break;
                write(fileno(stdout), buffer, strlen(buffer));
        }
        exit(EXIT_SUCCESS);
        return 0;
}

