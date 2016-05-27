/*************************************************************************
	> File Name: TwoPart.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月22日 星期二 19时42分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
//#define N 8

void Find(int a[], int key, int n){
    int low = 0, high = n - 1;
    int mid;
    while(low <= high){
        mid = (low + high)/2;
        if(key == a[mid]){
            printf("min = max, 即该数所在位置为%2d\n", mid);
            break;
        } 
        if(key < a[mid]) high = mid - 1;
        else low = mid + 1;
    }
    
    if(low > high)
        printf("数组中无该元素,min = %d, max = %d\n",low, high );
}

main( void )
{
    int *a, i, n;
    int num;

    printf("请输入数组长度:\n");
    scanf("%d", &n);
    a = (int *)malloc(n * sizeof(int));

    printf("请输入一组有序的数据(%d个)：\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", a+i);
    printf("请输入您要查找的数:");
    scanf("%d", &num);

    if(num < a[0])
        printf("数组中无该数据，并且它小于数组中最小元素。即min = %d\n", 0);
    else if(num > a[n-1])
    printf("数组中无该数据，并且它大于数组中最大元素。即max = %d\n", n-1);
    else
        Find(a, num, n);

    free(a);
}
