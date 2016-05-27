/*************************************************************************
	> File Name: narcissistic.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年03月27日 星期日 17时58分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main( void ){
    int m, n;
    int i;
    int flag = 0;

    scanf("%d %d", &m, &n);
    if(m < 100 || m >= n || n > 999){
        exit(0);
    }

    for(i = m; i <= n; i++){
        int r = i;
        int k = 0;

        while(r != 0){
            k += pow(r % 10, 3);
            r = r / 10;
        }

        if(k == i){
            flag = 1;
            printf("%d ",i);
        }
    }

    if(flag == 0){
        printf("no\n");
    }
}
