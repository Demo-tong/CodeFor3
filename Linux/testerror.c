/*************************************************************************
	> File Name: testerror.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月13日 星期日 14时59分37秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>

main(int argc, char** argv)
{
    errno = EPERM;
    perror(argv[0]);
    return 0;
}
