/*************************************************************************
	> File Name: hun_chicken.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月23日 星期五 14时07分17秒
 ************************************************************************/

#include<stdio.h>
int main(int argc, char*argv[])
{
    int x, y, z;
    for(x = 0; x < 20; x++)
    for(y = 0; y < 33; y++){
        z = 100 - x - y;
        if((5 * x + 3 * y + (1.0/2) *z) == 100)
            printf("公鸡：%d , 母鸡：%d , 小鸡：%d\n",x, y, z );
    }

    return 0;
}
