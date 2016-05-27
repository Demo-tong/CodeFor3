/*************************************************************************
	> File Name: fork_lockf.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月27日 星期二 10时59分12秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int p1, p2;
    int i;

    if(p1 = fork()){
        lockf(1, 1, 0);
        for(i = 0; i < 10; i++)
            printf("child%d\n", i);
        lockf(1, 1, 0);
    }

    else{
        if(p2 = fork()){
            lockf(1, 1, 0);
            for(i = 0; i < 10; i++)
                printf("son%d\n", i);
            lockf(1, 1, 0);
        }else{
            lockf(1, 1, 0);
            for(i = 0; i < 10; i++)
                printf("daughter%d\n", i);
            lockf(1, 0, 0);
        }
    }
}
