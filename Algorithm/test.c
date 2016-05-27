/*************************************************************************
	> File Name: test.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月23日 星期五 19时43分23秒
 ************************************************************************/

#include<stdio.h>
#define f(n) n*n
int main(int argc, char*argv[])
{
    int a = 9;
    int b = 3;
    int c = f(a)/f(b);
    printf("%d\n", c);
    /*
    struct data{
        int a;
        char b;
        double c;
    };

    printf("%d\n", sizeof(struct data));*/
}
