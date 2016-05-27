/*************************************************************************
	> File Name: machine_plan.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月03日 星期四 20时03分45秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


//排序，将每个作业所需时间安从大到小顺序排列
void Sort(int *t, int n){
    int i, j;
    int temp;

    for(i = 1; i <= n; i++){
        for(j = i+1; j <= n; j++){
            if(t[i] < t[j]){
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
}

int Min(int *s, int m){
    int i;
    int min_s;

    min_s = 1;
    for(i = 2; i <= m; i++){
        if(s[min_s] > s[i]){
            min_s = i;
        }
    }

    return min_s;
}

int Max(int *s, int m){
    int i, max_s;

    max_s = 1;
    for(i = 2; i <= m; i++){
        if(s[max_s] < s[i]){
            max_s = i;
        }
    }

    return max_s;
}

//处理机分配方案及获取最小的分配时间
int Arrange(int *t, int *s, int n, int m){
    int min;//最小时间
    int i, j;
    int mm, ma;//mm记录分配时间总和最小机器号

    for(i = 1; i <= n; i++){
        mm = i;
        if(mm <= m && s[i] == 0){
            printf("将机器%d从0到%d分配作业%d\n", mm, t[i], i);
            s[mm] += t[i];
        }else if(mm <= m){
            continue;
        }else{
            mm = Min(s, m);
            printf("机器%d所分配时间和最小,所以将该机器从%d到%d分配作业%d\n", mm, s[mm], s[mm]+t[i], i);
            s[mm] += t[i];
        }
    }

    ma = Max(s, m);

    return ma;
}


int main(){

    int i, j;//循环变量
    int n, m;//n表示作业个数，m表示机器数
    int *t, *s;//t:作业所需时间，s:各机器当前分配总耗时
    int minTime;

    printf("Please input the numbers of jobs and machine:\n");
    scanf("%d%d", &n, &m);

    t = (int *)malloc((n+1) * sizeof(int));
    s = (int *)malloc((m+1) * sizeof(int));

    //初始化s数组，开始每个机器当前所分配时间总和为0
    for(i = 1; i <= m; i++){
        s[i] = 0;
    }

    printf("Please input the time that every job needs:\n");
    for(i = 1; i <= n; i++){
        scanf("%d",t+i);
    }

    Sort(t, n);
    if(n <= m){
        minTime = t[1];
        printf("为每个机器分配一个作业，所需的最短时间为:%d\n", minTime);
    }else{
        minTime = Arrange(t, s, n, m);
        printf("该分配方法最多耗费时间%d,所需时间为:%d\n", minTime, s[minTime]);
    }
    return 0;
}
