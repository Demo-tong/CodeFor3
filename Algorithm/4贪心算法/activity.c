/*************************************************************************
	> File Name: activity.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月20日 星期五 08时52分39秒
 ************************************************************************/

#include<stdio.h>
#define N 11

int s[N+1];     //存储活动开始时间
int f[N+1];     //存储活动结束时间
int b[N+1];     //存储活动被安排状态,0表示未被安排，1表示被安排

void Input(){
    int i ;
    //FILE *fp;
    //fp = fopen("act.txt","r");
    printf("请输入%d个活动的开始时间以及结束时间:\n", N);
    for(i = 1; i <= N; i++){
        scanf("%d%d",s+i, f+i);
    }
   /* printf("有如下活动待安排:\n");
    printf("    开始时间    结束时间\n");
    while((fscanf(fp, "%d %d", s+i, f+i)) != EOF){
        printf("\t%d\t%d\n", s[i++], f[i++]);
        //fscanf(fp, "%d%d", s+i, f+i);
    }

    fclose(fp);*/
}


void Sort(){
    int i, j;
    int temps, tempf;
    
    for(i = 0; i <= N; i++){
        for(j = i+1; j <= N; j++){
            if(f[i] > f[j]){
                temps = s[i];   tempf = f[i];
                s[i] = s[j];    f[i] = f[j];
                s[j] = temps;   f[j] = tempf;
            }
        }
    }
}

void GreedSelect(){
   
    //第一个活动肯定被安排
    int j = 1;
    b[1] = 1;
    int i;

    for(i = 2; i <= N; i++){
        if(s[i] > f[j]){
            //后一个的开始时间大于前一个活动结束时间
            b[i] = 1;
            j = i;
        }else{
            b[i] = 0;
        }
    }
}


void Output(){
    int i;

    printf("具体活动安排如下:\n");
    for(i = 1; i <= N; i++){
        if(b[i] == 1){
            printf("%d号活动,开始时间%d,结束时间%d\n", i, s[i], f[i]);
        }
    }
}
int main(){
    //输入活动信息
    Input();

    //按照结束时间升序活动排序
    Sort();

    //具体活动安排
    GreedSelect();

    //输出活动安排
    Output();
}
