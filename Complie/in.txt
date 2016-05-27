/*************************************************************************
	> File Name: array.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年03月27日 星期日 18时29分45秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main( void ){
    int n, m;
    int i;
    double sum;

    scanf("%d %d", &n, &m);
    double *p = malloc(sizeof(double) * m);
    p[0] = n;
    sum = p[0];

    for(i = 1; i < m; i++){
        p[i] = sqrt(p[i-1]);
        sum += p[i];
    }

    printf("%.2lf\n", sum);
}
