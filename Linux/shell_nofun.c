/*************************************************************************
	> File Name: myshell.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月19日 星期四 14时02分19秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    char argv[10][10];
    int argc, i;
    pid_t pid;

  while(1){
        printf("Please input the order:");
        for(i = 0; ; i++){
            scanf("%s",argv[i]);
            if(getchar() == '\n')
                break;
        }
        argc = i+1;

        char path[100] = {"/bin/"};
        for(i = 0; i <sizeof(argv[0]); i++){
            path[5+i] = argv[0][i];
        }

        path[5+sizeof(argv[1])] = '\0';

        switch(argc){
            case 1:     
                if(fork() == 0)
                    if(execl(path, argv[0], (char*)0) == -1)
                        printf("error 1\n");
                break;
            case 2:
                if(fork() == 0)
                    if(execl(path, argv[0], argv[1], (char*)0) == -1)
                        printf("error 2");
                break;
            case 3:
                if(fork() == 0)
                    execl(path, argv[0], argv[1], argv[2], (char*)0);
                break;
            default:
                printf("The parameter is too many!\n");
        }

        wait(&pid);
    }
    return 0;
}
