#include <stdio.h>
#include <signal.h>
void main(int argc,char *argv[]){
        int pid,signo;
        if(argc!=3) {
                printf("usage: killsender pid signo\n"); 
                return;  
        }
        sscanf(argv[1],"%d",&pid); //获取参数pid    
        sscanf(argv[2],"%d",&signo); //获取参数signo   
        if(kill(pid,signo)<0)   {//发送信号     
                perror("kill");     
                return;   
        }  
        printf("ok: send out signal via kill system call!\n");    

}
