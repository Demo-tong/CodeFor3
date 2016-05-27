/*************************************************************************
	> File Name: work_plan.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月03日 星期四 22时03分14秒
 ************************************************************************/
    #include<stdio.h>

    int n,cost=0;  
    int x[100],c[100][100];  
      
    void work(int i,int count){  
        int j;

        if(i>n && count<cost){  
          cost = count;  
          return ;  
        }  
        if(count<cost)  
          for(j=1;j<=n;j++)  
            if(x[j] == 0){    
              x[j] = 1;    
              work(i+1,count+c[i][j]);    
              x[j] = 0;    
             }  
    }  
      
    int main(){
        int i,j;

        scanf("%d", &n);
        for(i=1;i<=n;i++){  
          for(j=1;j<=n;j++){  
            scanf("%d", &c[i][i]);  
            x[j] = 0;    
          }  
          cost+=c[i][i];    
        }  

        printf("%2d\n",cost);
        work(1,0);  
        printf("%2d\n",cost);  

        return 0;  
    }  
