#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
struct flock *file_lock(short type,short whence){
    static struct flock fl;
    fl.l_type = type;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_whence = whence;
    fl.l_pid = getpid();
    return &fl;
}
int main(int argc,char *argv[]){

     int fp,fork_id;
     char data[1024];
     if(argc == 1){
         return -1;   
     }
     if((fork_id = fork()) > 0){
        int read_long = 0;
        while(1){
             sleep(3);
             fp = open(argv[1],O_RDONLY|O_CREAT,0640);
             fcntl(fp,F_SETLKW,F_WRLCK,SEEK_SET);
             if(fp > 0){
                 printf("文件内容为:\n");
                 while((read_long = read(fp,data,sizeof(data)/sizeof(char))) > 0){
                      data[read_long] = '\0';
                      printf("%s",data);
                 } 
                 printf("\n");      
             }else{
                 perror(argv[1]);
             }
             fcntl(fp,F_SETLKW,file_lock(F_UNLCK,SEEK_SET));
             close(fp);
        }
     }else if(fork_id == 0){
        int num_write = 0;
        while(1){
             sleep(1);
             fp = open(argv[1],O_WRONLY|O_CREAT|O_APPEND,0640);
             fcntl(fp,F_SETLKW,F_WRLCK,SEEK_SET);
             char str[20];
             sprintf(str," %d",num_write);
             write(fp,str,strlen(str));
             if(fp <= 0){
                 perror(argv[1]);
             }
             fcntl(fp,F_SETLKW,file_lock(F_UNLCK,SEEK_SET));
             close(fp);
             num_write++;
        }
     }else if(fork_id < 0 ){
        perror(argv[1]);
     }
     return 0;
}
