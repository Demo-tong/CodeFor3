/*************************************************************************
	> File Name: show.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月13日 星期日 15时16分42秒
 ************************************************************************/

#include<stdio.h>

main(int argc, char*argv[])
{
    int i;
    for(i = 1; i < argc; i++)
    printf("%s\n", argv[i]);
}
