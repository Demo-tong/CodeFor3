/*************************************************************************
	> File Name: knapsack.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年10月21日 星期三 08时53分33秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define N 3
#define c 11
#define d 10

// 求两数中较大者
int max(int m, int n){
    if(m < n)
        return n;
    return m;
}

//求两数中较小者
int min(int m, int n){
    if(m < n)
        return m;
    return n;
}

int m[N+1][c+1][d+1];   //存储当前背包物品的价值

//物品放置方案
void knapsack(int *w, int *v, int *b, int n){
    //首先判断第N个物品的放置状态
    int jMax = min(w[1] - 1, c);
    int dMax = min(b[1] - 1, d);
    int i, j, k;

    //将m[][][]数组第一个物品对应价值值赋为0
    for(i = 0; i <= jMax; i++)
        for(j = 0; j <= d; j++)
            m[1][i][j] = 0;//未装入物品，则背包内价值为0
    
    for(i = 0; i <= dMax; i++)
        for(j = 0; j <= c; j++)
            m[1][j][i] = 0;

    for(i = w[1]; i <= c; i++)
        for(j = b[1]; j <= d; j++)
            m[1][i][j] = v[1];//装入该物品，则背包价值为当前物品的价值
    
    for(i = 2; i < n; i++){
        /*从第n-1个物品开始，找出每一个物品重量减1与背包容量c之间较小者,
         * 将m[][]数组中第i行，0～w[i]-1列之间赋值为对应上一个物品的价值（在此容量下不能放之下该物品）
         *在w[i]~c之间赋值为计算出的价值
         */
        jMax = min(w[i] - 1, c);
        dMax = min(b[i] - 1, d);

        for(j = 0; j <= jMax; j++)
		    for(k = 0; k <= d; k++)
                m[i][j][k] = m[i-1][j][k];

        for(j = 0; j <= dMax; j++)
            for(k = 0; k <= c; k++)
                m[i][k][j] = m[i-1][k][j];
        for(j = w[i]; j <= c; j++)
        for(k = b[i]; k <= d; k++)
            m[i][j][k] = max(m[i-1][j][k], m[i-1][j-w[i]][k-b[i]] + v[i]);
    }

    m[n][c][d]= m[n-1][c][d];
    if(c >= w[n] && d >= b[n])
	m[n][c][d] = max(m[n][c][d], m[n-1][c-w[n]][d-b[n]] + v[n]);
}


void Traceback(int *w, int *x, int *b, int n){
    int i;
    int r_c = c;
    int r_d = d;

    for(i = n; i > 1; i--){
        if(m[i][r_c][r_d] == m[i-1][r_c][r_d])
            x[i] = 0;//说明为装入第i个物品
        else{
            x[i] = 1;
            r_c -= w[i];
            r_d -= b[i];
        }
    }

    x[1] = (m[1][r_c][r_d]) ? 1 : 0;
}


void Print(int *w, int *v, int *b, int *x, int n){
    int i;
    float sum = 0.0;
    printf("在背包容量为%d、体积为%d时,物品装入方案如下:\n", c, d);

    for(i = 1; i <= n; i++){
        if(x[i] == 1){
            printf("装入第%d个物品，其重量为%d,体积为%d,价值为%d\n", i, w[i], b[i], v[i]);
            sum += v[i];
        }
    }

    printf("背包中总价值为:%.1f\n", sum);
}


/*0-1背包问题：
 * 给定n种物品和一个背包。物品i的重量为wi，其价值是vi，背包容量为c,背包体积为d。
 * 如何选择装入背包中的物品，使得装入的物品价值最大
 */
int main()
{
    int n;

    int *w = (int *)malloc((N+1) * sizeof(int));//商品重量
    int *v = (int *)malloc((N+1) * sizeof(int));//商品价值
    int *b = (int *)malloc((N+1) * sizeof(int));//商品体积
    int *x = ( int *)malloc((N+1) * sizeof(int));
   
    int i;
    printf("请输入%d个物品的重量、价值、体积:\n", N);
    for(i = 1; i <= N; i++){
        scanf("%d%d%d", w + i, v + i, b + i);
    }

    //调用函数决策方案
    knapsack(w, v, b, N);
    Traceback(w, x, b, N);

    //打印装包方案
    Print(w, v, b, x, N);

    free(w);
    free(v);
    free(x);
}
