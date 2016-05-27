/*************************************************************************
	> File Name: num_Trangle.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月20日 星期五 08时48分31秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

int main(){
    int num;//num为三角形行高
    int i, j;//循环变量
    int **p;
    int max[100][100];
    int max_num;

    printf("请输入三角形的行数:\n");
    scanf("%d",&num);

    p = (int **)malloc(num * sizeof(int*));

    //输入数字
    for(i = 0; i < num;i++){
        p[i] = (int *)malloc((i+1) * sizeof(int));
        for(j = 0; j <= i; j++){
            scanf("%d", &p[i][j]);
        }
    }

    //将max[]数组初始化为二维数组最后一行的各值
    for(j = 0; j < num; j++)
        max[num-1][j] = p[num-1][j];
    

    //计算数字和
    for(i = num-1; i > 0; i--){
        for(j = 0; j < i; j++){
            max[i-1][j] = (max[i][j] > max[i][j+1]?max[i][j]:max[i][j+1])+p[i-1][j];
            /*if(max[i][j] > max[i][j+1]){
                max[i-1][j] = max[i][j] + p[i-1][j];
            }else{
                max[i-1][j] = max[i][j+1] + p[i-1][j];
            }*/
        }
    }

    printf("\n\n数字三角形中的各数如下:\n");
    for(i = 0; i < num; i++){
        for(j = 0; j <= i; j++){
            printf("%-2d",p[i][j]);
        }
        printf("\n");
    }

    printf("The max result is: %d\n", max[0][0]);

    for(i = 0; i < num; i++){
        free(p[i]);
        //free(p);
    }
    return 0;
}
