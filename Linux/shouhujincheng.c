#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAXFILE 65535
volatile sig_atomic_t isRun = 1;
void sigterm_handler(int arg)
{
    isRun = 0;
}
int main(void){
   
     pid_t pid = -1,s_pid = -1;
     char *hello = "Hello world!\n";
     int fd,i;
     if((pid = fork()) == 0){//1
           s_pid = setsid();//2
           if (s_pid < 0){
               perror("setsid error");
               exit(EXIT_FAILURE);
           }
           chdir("."); //3
           umask(0);//4
           for(i = 0;i < MAXFILE ;i++)//5
                close(i);
           signal(SIGTERM, sigterm_handler); //6
           printf("isRun :%d\n",isRun);          
           while(isRun){
               if((fd = open("hello",O_WRONLY|O_CREAT|O_APPEND,0640))==-1){
                    perror("hello");
                    exit(EXIT_FAILURE);
               }
               write(fd,hello,strlen(hello));
               close(fd);
               sleep(1);
           }
     }else if(pid == -1){
          perror("hello");
          exit(EXIT_FAILURE);
     }else if(pid>0){
          printf("%d\n",(int)pid);
	  exit(0);
	 }
     return 0; 
}
