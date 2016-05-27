/*************************************************************************
	> File Name: mmap_file.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年11月18日 星期三 19时12分54秒
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv){

    int fd;
    char *mepped_mem, *p;
    int length = 1024;//定义文件长度为1024
    void *start_addr = 0;

    fd = open(argv[1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);//打开文件
    length = lseek(fd, 1, SEEK_END);//求文件长度
    write(fd, "\0", 1);
    lseek(fd, 0, SEEK_SET);//文件指针设置到开始位置
    mepped_mem = mmap(start_addr, length, PROT_READ, MAP_PRIVATE, fd, 0);//执行映射
    printf("%s\n", mepped_mem);

    close(fd);
    munmap(mepped_mem, length);
    return 0;
}
