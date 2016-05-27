/*************************************************************************
	> File Name: 0_1Pack.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月08日 星期二 11时48分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int c, n;//c背包容量,n物品个数
int cw = 0, cv = 0, bestV = 0;//cw当前重量，cv当前价值，bestV最大价值
int *w, *v;//w存放物品对应重量，v存放物品对应价值
int *order, *x;//存放物品放置状态


//按单位价值从大到小将物品排序
void Sort(){
    int i, j;
    int tempW, tempV, tempO;//临时变量

    double *perV = (double *)malloc((n+1) * sizeof(double));
    for(i = 1; i <= n; i++){
        perV[i] =1.0 * v[i]/w[i];
    }

    //冒泡法排序
    for(i = 1; i < n; i++){
        for(j = i+1; j <= n; j++){
            if(perV[i] < perV[j]){
                tempW = w[i];   tempV = v[i];   tempO = order[i];
                w[i] = w[j];    v[i] = v[j];    order[i] = order[j];
                w[j] = tempW;   v[j] = tempV;   order[j] = tempO;
            }
        }
    }

    free(perV);
}


//计算上界值
int Bound(int k){
    //剩余重量
    int restW = c - cw;
    int b = cv;

    //以物品单位重量价值递减装入
    while(k <= n && w[k] <= restW){
        restW -= w[k];
        b += v[k];
        k++;
    }

    if(k <= n){
        b += v[k]/w[k] * restW;    
    }

    return b;
}


void BackTrack(int t){
    int i;
    
    if(t > n){
        bestV = cv;
        return;
    }

    //进入左子树
    if(cw + w[t] <= c){
        cw += w[t];
        cv += v[t];
        x[t] = 1;
        BackTrack(t+1);
        cw -= w[t];
        cv -= v[t];
        //x[t] = 0;
    }

    //进入右子树，进行减枝
    if(Bound(t+1)>bestV){
        BackTrack(t+1);
    }
}


int main(){

    int i;

    printf("请输入背包可容纳的最大重量以及物品个数:\n");
    scanf("%d%d", &c, &n);

    w = (int *)malloc((n+1) * sizeof(int));
    v = (int *)malloc((n+1) * sizeof(int));
    x = (int *)malloc((n+1) * sizeof(int));
    order = (int *)malloc((n+1) * sizeof(int));

    printf("请输入%d个物品对应的重量及价值:\n", n);
    for(i = 1; i <= n; i++){
        scanf("%d%d", w+i, v+i);
        order[i] = i;
    }

    Sort();
    BackTrack(1);

    printf("最大价值:%d\n应装入物品:", bestV);

    for(i = 1; i <= n; i++){
        if(x[i] == 1){
            printf("%2d", order[i]);
        }
    }

    printf("\n");

    free(w);
    free(v);
    free(x);
    free(order);

    return 0;
}
