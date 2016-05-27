/*************************************************************************
	> File Name: fork_sen.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月27日 星期二 10时52分01秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    int p1, p2;
    int i;
    if(p1 = fork())
        for(i = 0; i < 5; i++){
            printf("child%d, ID:%d\n", i, getpid());
            usleep(600);
        }
    else if(p2 = fork())
        for(i = 0; i < 5; i++){
            printf("son%d,ID:%d\n", i, getpid());
            usleep(600);
        }
        else
            for(i = 0; i < 5; i++){
                printf("daughter%d,ID:%d\n", i, getpid());
                usleep(600);
            }

    printf("\n");
}
