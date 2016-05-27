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


//物品放置方案
void knapsack(int *w, int *v, int m[][c+1], int n){
    //首先判断第1个物品的放置状态
    int jMax = min(w[1] - 1, c);
    int i, j;

    //将m[][]数组中1行，0～jMax列之间的值赋为0
    for(i = 0; i <= jMax; i++)
       m[1][i] = 0;//未装入物品，则背包内价值为0
    for(i = w[1]; i <= c; i++)
       m[1][i] = v[1];//装入该物品，则背包价值为当前物品的价值
    for(i = 2; i < n; i++){
        /*从第n-1个物品开始，找出每一个物品重量减1与背包容量c之间较小者,
         * 将m[][]数组中第i行，0～w[i]-1列之间赋值为对应上一个物品的价值（在此容量下不能放之下该物品）
         *在w[i]~c之间赋值为计算出的价值
         */
        jMax = min(w[i] - 1, c);
        for(j = 0; j <= jMax; j++)
		m[i][j] = m[i-1][j];
        for(j = w[i]; j <= c; j++)
            m[i][j] = max(m[i-1][j], m[i-1][j-w[i]] + v[i]);
    }

    m[n][c] = m[n-1][c];
    if(c >= w[n])
	m[n][c] = max(m[n][c], m[n-1][c-w[n]] + v[n]);
}


void Traceback(int *w, int m[][c+1], int *x, int n){
    int i;
    int r_c = c;

    for(i = n; i > 1; i--){
        if(m[i][r_c] == m[i-1][r_c])
            x[i] = 0;//说明为装入第i个物品
        else{
            x[i] = 1;
            r_c -= w[i];
        }
    }

    x[1] = (m[1][r_c]) ? 1 : 0;
}


void Print(int *w, int *v, int *x, int n){
    int i;
    float sum = 0.0;
    printf("在背包容量为%d时，物品装入方案如下:\n", c);

    for(i = 1; i <= n; i++){
        if(x[i] == 1){
            printf("装入第%d个物品，其重量为%d,价值为%d\n", i, w[i], v[i]);
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
    int n;

    int *w = (int *)malloc((N+1) * sizeof(int));//商品重量
    int *v = (int *)malloc((N+1) * sizeof(int));//商品价值
    int m[N+1][c+1];//存储当前背包中物品的价值
    int *x = ( int *)malloc((N+1) * sizeof(int));
   
    int i;
    printf("请输入%d个物品的重量以及对应的价值:\n", N);
    for(i = 1; i <= N; i++){
        scanf("%d%d", w + i, v + i);
    }

    for(i = 1; i <= N;){
        if(w[i] > c){
            ++i;
        }else{
            break;
        }
    }

    if(i > N)
        printf("当前所有物品的重量大于背包重量，所以无放置方案!\n");
    else{
        //调用函数决策方案
        knapsack(w, v, m, N);
        Traceback(w, m, x, N);

        //打印装包方案
        Print(w, v, x, N);
    }

    free(w);
    free(v);
    free(x);

    return 0;
}
