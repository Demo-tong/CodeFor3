/*************************************************************************
	> File Name: myshell.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月19日 星期四 14时02分19秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


void readCmd(int *argc, char comm[][10]){
    int i = 0;

    while(i >= 0){
        scanf("%s",comm[i]);

        if(getchar() == '\n')
            break;
        i++;
    }

    *argc = i+1;//保存参数个数
}

void doCommand(int argc, char comm[][10]){
    int i;//循环变量
    char path[50] ={ "/bin/"};//命令的查找目录
    
    for(i = 0; i < sizeof(comm[0]); i++){
        path[5+i] = comm[0][i];
    }

    path[5+sizeof(comm[0])] = '\0';

    //子进程执行命令
    switch(argc){
        case 1:     
           if(strcmp(comm[0], "exit") == 0)//若输入命令为exit则退出该程序
                exit(0);
            
            if(fork() == 0)
                if(execl(path, comm[0], (char*)0) == -1)
                    printf("error 1\n");
            break;
        case 2:
            if(fork() == 0)
                if(execl(path, comm[0], comm[1], (char*)0) == -1)
                    printf("error 2");
            break;
        case 3:
            if(fork() == 0)
                execl(path, comm[0], comm[1], comm[2], (char*)0);
            break;
        default:
            printf("The parameter is too many!\n");
    }


}

int main(){
    char comm[10][10];//保存输入的命令
    int argc, i;//argc保存输入的命令个数
    pid_t pid;

    //创建子进程
    //pid = fork();

    //循环调用函数执行命令
    for( ; ; ){
        printf("Please input the order:\n");
        readCmd(&argc, comm);
        doCommand(argc, comm);
        wait(&pid);//wait()函数会暂时停止目前进程的执行，直到有信号来到或子进程结束
    }

    return 0;
}
