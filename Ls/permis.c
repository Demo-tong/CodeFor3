/*************************************************************************
	> File Name: permis.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年05月18日 星期三 18时30分44秒
 ************************************************************************/

//文件权限
#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h> 
void main( int argc, char **argv ) 
{ 	int fd, n; 
	char buf[ 15 ]; // 没有输入目标文件
	if ( argc == 1 ) 
	{ 
		printf( "输入错误，请按照如下格式：\n./my_file 文件名或文件路径\n" ); 
		exit( 0 ); 
	} 
	// 第一次打开文件
	fd = open( argv[1], O_RDONLY ); 
	if ( fd == -1 ) 
	{ 
		printf( "文件打开错误，文件权限不够或不存在！\n" ); 
		exit( 0 ); 
	} 
	//首次读取文件的内容
	printf( "第一次打开文件操作\n" ); 
	n = read( fd, buf, 10 ); 
	buf[ n ] = '\0'; 
	printf( "NO.1 读取%d字节的数据:%s", n, buf ); 
	printf( "\n修改文件权限\n" ); 
	sleep( 20 );// 睡眠20秒
	// 再次读取文件内容
	printf( "\n睡眠20秒结束\n" ); 
	n = read( fd, buf, 10 ); 
	buf[ n ] = '\0'; 
	printf( "NO.2 读取了%d字节的数据：%s", n, buf ); 
	close( fd ); 
	printf( "\n关闭文件\n" ); 
	// 再次打开文件
	printf( "\n第二次打开文件操作\n" ); 
	fd = open( argv[1], O_RDONLY ); 
	if ( fd == -1 ) 
	{ 
		printf( "文件打开错误，文件权限不够或不存在！\n" ); 
		exit( 0 ); 
	} 
	close( fd ); 
} 

