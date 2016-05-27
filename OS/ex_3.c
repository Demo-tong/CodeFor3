/*************************************************************************
	> File Name: ex_3.c
    >Description:按时间片轮转法实现处理器调度的程序
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月17日 星期二 10时47分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct PNode{//PCB
    struct PNode *next;     //定义指向下一个节点的指针
    char name[10];          //定义进程名，并分配空间
    int All_Time;           //定义总运行时间
    int Runed_Time;         //定义已运行时间
    char state;             //定义进程状态ready/end
}Proc;//定义指向该PCB的指针

int ProcNum;//总进程个数

//初始化就绪队列
void InitPCB(Proc **H){
    printf("请输入总进程个数:\n");
    scanf("%d", &ProcNum);

    int Num = ProcNum;

    *H = (Proc**)malloc(sizeof(Proc*));//建立头节点
    *H->next = NULL;

    Proc *p = **H;
    printf("总进程个数为%d个，请依次输入相应信息\n", Num);

    while(Num--){
        p = p->next = (Proc*)malloc(sizeof(struct PNode));
        printf("进程名 总运行时间 已运行时间:\n");
        scanf("%s%d%d", p->name, &p->All_Time, &p->Runed_Time);
        p->state = 'R';
        p->next = NULL;
    }

    p->next = *H->next;
}

//输出运行中的进程信息
void DispInfo(Proc H){
    Proc p = H->next;

    if(p == NULL){
        printf("error");
        exit(0);
    }
    do{
        if(p->state != 'E'){
            //如果该进程状态不是End
            printf("进程名:%s\t总运行时间:%d\t已运行时间:%d\t状态:%c\n",p->name, p->All_Time, p->Runed_Time, p->state);
            p = p->next;
        }else{
            p = p->next;
        }
    }while(p != H->next);

}

//时间片轮转法
void SJP_Simulator(Proc H){
    printf("-----------------------------------------start-------------------------------------------\n");
    int flag = ProcNum;//记录剩余进程数
    int round = 0;//记录轮转数

    Proc p = H->next;

    while(p->All_Time > p->Runed_Time){
        //即未结束的进程
        round++;
        printf("\nRound %d--正在运行%s进程\n", round, p->name);
        p->Runed_Time++;//更改正在运行的进程已运行时间
        DispInfo(H);//输出此时为就绪状态的进程的信息

        if(p->All_Time == p->Runed_Time){
            //判断该进程是否结束  
            p->state = 'E';
            flag--;
            printf("%s进程已运行结束，进程被删除!\n",p->name);
        }

        p = p->next;
        while(flag && (p->All_Time == p->Runed_Time)){
            p = p->next;//跳过先前已结束的进程
        }
    }

    printf("-----------------------------------------End-------------------------------------------\n");
}

int main(int argc, char*argv[]){
    Proc *H;

    InitPCB(&H);//数据初始化
    DispInfo(H);//输出此刻进程的状态信息
    SJP_Simulator(H);//时间片轮转法
    system("clear");
}
