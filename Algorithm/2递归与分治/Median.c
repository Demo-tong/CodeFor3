/*************************************************************************
	> File Name: Median.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月23日 星期三 08时33分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


/*
 * 函数名:getMedian(int *arr1, int *arr1, int n)
 * 函数功能:查找两数组合并后的中位数
 * 思想:当使用二分查找时两个分数组中位数相等，则这个值为两数组合并后的中位数。
 * 当前一个中位数小于后一个中位数，则取第一个数组中后半部分以及第二个数组中的前半部分继续查找中位数;
 * 否则作相反的操作
 * */


//获取两个书中较小者以及较大者
int min(int a, int b){
    return (a < b)?a:b;
}
int max(int a, int b){
    return (a > b)?a:b;
}

//求数组中位数
int Median(int *arr, int n){
    if(n%2 == 0){
        return (arr[n/2] + arr[n/2-1])/2;
    }else{
        return arr[n/2];
    }
}

//获取中位数
int getMedian(int *arr1, int *arr2, int n){
    int m1, m2;//保存两个数组的中位数

    if(n <= 0){
        return -1;
    }

    //递归终止条件
    if(n == 1){
        return (arr1[0]+arr2[0])/2;
    }
    if(n == 2){
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1]))/2;
    }

    m1 = Median(arr1, n);
    m2 = Median(arr2, n);

    
    //当两个数组中位数相等，则合并后中位数即为该值
    if(m1 == m2){
        return m1;
    }

    //若m1<m2则进行以下操作
    if(m1 < m2){
        if(n%2 == 0){
            return(getMedian(arr1+n/2-1, arr2, n/2+1));
        }else{
            return (getMedian(arr1+n/2, arr2, n/2+1));
        }
    }else{
        if(n%2 == 0){
            return (getMedian(arr2+n/2-1, arr1, n/2+1));
        }else{
            return (getMedian(arr2+n/2, arr1, n/2+1));
        }
    }
}

int main(){
    int *arr1, *arr2;
    int n;
    int i;

    printf("请输入数组长度:\n");
    scanf("%d", &n);

    arr1 = (int *)malloc(sizeof(int) * n);
    arr2 = (int *)malloc(sizeof(int) * n);

    printf("请输入第一个数组的%d个有序数:\n", n);
    for(i = 0; i < n; i++){
        scanf("%d", arr1+i);
    }

    printf("请输入第二个数组的%d个有序数:\n", n);
    for(i = 0; i < n; i++){
        scanf("%d", arr2+i);
    }
    //int n1 = sizeof(arr1)/sizeof(int);
    //int n2 = sizeof(arr2)/sizeof(int);

    //if(n1 == n2){
    printf("Median is %d\n", getMedian(arr1, arr2, n));
    //}else{
      //  printf("Doesn't work for arrays of unequal size");
    //}

    free(arr1);
    free(arr2);

    return 0;
}
