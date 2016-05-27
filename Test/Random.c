/*************************************************************************
	> File Name: Random.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年03月28日 星期一 20时34分16秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>

int main(void){
    int n, b;
    int i;
    int left = 0, right = 0;
    int min;

    scanf("%d %d", &n, &b);
    for(i = 1; i <= n; i++){
        if(i < b){
            left++;
        }else{
            right++;
        }
    }
    if(left < right){
        printf("%d\n", b+1);
    }else{
        printf("%d\n", b-1);
    }

}
