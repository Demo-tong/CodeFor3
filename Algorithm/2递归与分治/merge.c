/*************************************************************************
	> File Name: merge.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年09月22日 星期二 17时25分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void Merge(int a[], int left, int mid, int right){
    int i = left, j = mid + 1;
    int k = 0;

    int *b = malloc((left + right + 1) * sizeof(int));

    //合并具体实现
    while(i <= mid && j <= right){
        if(a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }

    while(i <= mid)
        b[k++] = a[i++];
    while(j <= right)
        b[k++] = a[j++];

    for(i = left, k = 0; i <= right; i++, k++)
        a[i] = b[k];

    free(b);
}

void MergeSort(int a[], int n){
    int size = 1;//size表示子数组的宽度
    int left, right, mid, i;
    //left表示待合并的数组中第一个数组的初始下标，而right表示第二个数组的末尾下标
    while(size <= n-1){
    //保证子数组的长度最大不大于N-1
    left = 0;
  //  i = 0;
        while(left + size <= n-1){
            mid = left + size -1;
            i = 0;
            right = mid + size;

            if(right > n-1)//当最后一组子数组长度未达到size，直接将right赋值为n-1
                right = n-1;
            Merge(a, left, mid, right);
            printf("(from %2d to %2d)", left, right);
            while(i < n){
                printf("%-6d", a[i++]);
            }
            printf("\n");
            //Merge(a, left, mid, right);
            left = right + 1;
        }

        size *= 2;
    }
}
main( void )
{
    int n;
    int i;

    printf("请输入数组长度:\n");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("请输入%d个数字:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", a+i);

    printf("Before sorted:\n");
    for(i = 0; i < n; i++)
        printf("%-3d", a[i]);
    printf("\n");

    MergeSort(a, n);
    
    printf("After sorted:\n");
    for(i = 0; i < n; i++)
        printf("%-3d", a[i]);
    printf("\n");
}
