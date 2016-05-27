/*************************************************************************
	> File Name: knapsack.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月21日 星期三 08时53分33秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>

// 求两数中较大者
float max(float m, float n){
    if(m < n)
        return n;
    return m;
}

//求两数中较小者
float min(float m, float n){
    if(m < n)
        return m;
    return n;
}


//物品放置方案
void knapsack(float c, float *w, float *v, float *m, int n){
    //首先判断第N个物品的放置状态
    float jMax = min(w[n] - 1, c);
    int i, j;

    //将m[][]数组中N行，0～jMax列之间的值赋为0
    for(i = 0; i <= jMax; i++)
       *((float *)m + n + i) = 0;//未装入物品，则背包内价值为0
    for(i = w[n]; i <= c; i++)
       *((float *)m + n + i) = v[n];//装入该物品，则背包价值为当前物品的价值
    for(i = n-1; i > 1; i--){
        /*从第n-1个物品开始，找出每一个物品重量减1与背包容量c之间较小者,
         * 将m[][]数组中第i行，0～w[i]-1列之间赋值为对应上一个物品的价值（在此容量下不能放之下该物品）
         *在w[i]~c之间赋值为计算出的价值
         */
        jMax = min(w[i] - 1, c);
        for(j = 0; j <= jMax; j++)
            *((float * )m + i * (int)c + j) = *((float *)m + (i+1) * (int)c + j);
        for(j = w[i]; j <= c; j++)
            *((float *)m + i *(int)c + j) = max(*((float *)m + (i+1) * (int)c + j), *((float *)m + (i+1) * (int)c + (j - w[i])) + v[i]);
            //m[i][j] = max(m[i+1][j], m[i+1][j-w[i]] + v[i]);
    }


    *((float *)m + 1 + c) = *((float *)m + 2 + c);
    //m[1][c] = m[2][c];
    if(c >= w[1])
        *((float *)m + 1 + c) = max(*((float *)m + 1 + c), *((float *)m + 2 + (c-w[1])) + v[1]);
        //m[1][c] = max(m[1][c], m[2][c-w[1]] + v[1]);
}


void Traceback(float c, float *w, float **m, int *x, int n){
    int i;

    for(i = 1; i < n; i++){
        if(*((float *)m + i + c) == *((float *)m + (i+1) + c))
            x[i] = 0;//说明为装入第i个物品
        else{
            x[i] = 1;
            c -= w[i];
        }
    }

    x[n] = (*((float *)m + n + c)) ? 1 : 0;
    printf("%d\n", x[n]);
}


void Print(float *w, float *v, int *x, int n, float c){
    int i;
    float sum = 0.0;
    printf("在背包容量为%f时，物品装入方案如下:\n", c);

    for(i = 1; i <= n; i++){
        if(x[i] == 1){
            printf("装入第%d个物品，其重量为%f,价值为%f\n", i, w[i], v[i]);
            sum += v[i];
        }
    }

    printf("背包中总价值为:%.1f\n", sum);
}


/*0-1背包问题：
 * 给定n钟物品和一个背包。物品i的重量为wi，其价值是vi，背包容量为c。
 * 如何选择装入背包中的物品，使得装入的物品价值最大
 */
int main()
{
    float c;
    int n;
    printf("请输入背包容量和物品个数:\n");
    scanf("%f%d", &c, &n);

    float *w = (float *)malloc((n+1) * sizeof(float));//商品重量
    float *v = (float *)malloc((n+1) * sizeof(float));//商品价值
    float *m = (float *)malloc((n + 1) * (int)(c + 1) * sizeof(float));//存储当前背包中物品的价值
    int *x = ( int *)malloc((n+1) * sizeof(int));
   
    int i;
    printf("请输入%d个物品的重量以及对应的价值:\n", n);
    for(i = 1; i <= n; i++){
        scanf("%f%f", w + i, v + i);
    }

    //调用函数决策方案
    knapsack(c, w, v, m, n);
    Traceback(c, w, m, x, n);

    //打印装包方案
    Print(w, v, x, n, c);

    free(w);
    free(v);
    free(x);
}
