#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
//SIGUSR1信号处理函数
void CbSigUsr1(int signo)  {//输出接收到的信号信息   
        printf("\nreceive signal=%d.\n",signo);
}
void main() {//安装SIGUSR1信号 
        if(signal(SIGUSR1,CbSigUsr1)==SIG_ERR){ 
                perror("signal");     
                return;
        }
        printf("my pid is %d\n",getpid());
        printf("waiting for SIGUSR1...\n");//暂停，等待信号
        pause();
}
