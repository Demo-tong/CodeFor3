/*************************************************************************
	> File Name: queen.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月08日 星期二 10时36分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
void Output();

int n, sum = 0;
int *x;


//判断前k个皇后是否与当前的皇后放置位置发生冲突
int Leagal(int k){
    int j;

	for (j = 1; j < k; j++){
		//不在同一列以及同一斜线
		if (k - j == abs(x[j] - x[k]) || x[j] == x[k])
			return 0;
	}

	return 1;
}

void BackTrack(int t){
    int i;

    if (t > n){
		sum++;//统计可行解的个数
        Output();
	}
	else{
		for (i = 1; i <= n; i++){
            x[t] = i;
			if (Leagal(t))   BackTrack(t + 1);
	    }
    }
}

//输出皇后放置方案
void Output(){

    int i, j;

    printf("(");
    for(i = 1; i <= n; i++){
        if(i < n)
            printf("%d,", x[i]);
        else
            printf("%d", x[i]);
    }
    printf(")\n");

}

int main(){
    
    int i;

	printf("请输入皇后的个数:\n");
	scanf("%d", &n);

	x = (int *)malloc((n+1) * sizeof(int));

	for (i = 1; i <= n; i++){
		x[i] = 0;//为x数组赋初值
	}

    printf("以下是%d个皇后可放置的坐标:\n", n);
	BackTrack(1);

    printf("共有%d种可行方案\n", sum);

    free(x);

	return 0;
}

