/*************************************************************************
	> File Name: echo.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月13日 星期日 15时20分51秒
 ************************************************************************/

#include<stdio.h>
main(int argc, char** argv)
{
    while(--argc > 0){
        printf("%s%c", *++argv, (argc > 1) ? ' ' : '\n');
    }
}
