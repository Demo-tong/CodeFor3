/*************************************************************************
	> File Name: fork.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月27日 星期二 10时46分05秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    int p1, p2;

    if(p1 = fork()){
        putchar('b');
        sleep(1);//使该进程休眠一秒
    }
    else{
        if(p2 = fork()){
            putchar('c');
            usleep(200);//使该进程休眠三秒
        }
        else{ 
            putchar('a');
            usleep(200);
        }
    }

    printf("\n");
    return 0;
}
