/*************************************************************************
	> File Name: ls1.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年05月09日 星期一 16时49分59秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void doLs(char[]);

int main(int argc, char*argv[]){
    if(argc == 1){
        doLs(".");
    }else{
        while(--argc){
            printf("%s:\n",*++argv);
            doLs(*argv);
        }
    }
}

void doLs(char dirname[]){
    DIR *dir_ptr;
    struct dirent *direntp;//读目录文件结构体

    if((dir_ptr = opendir(dirname)) == NULL){
        fprintf(stderr, "ls1:cannot open %s\n", dirname);
    }else{
        while((direntp = readdir(dir_ptr)) != NULL){
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}
