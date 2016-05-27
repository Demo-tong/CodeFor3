/*************************************************************************
	> File Name: path.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年05月18日 星期三 18时35分05秒
 ************************************************************************/

#include <linux/fs.h> 
#include <linux/init.h> 
#include <asm/unistd.h> 
#include <asm/uaccess.h> 
#include <linux/types.h> 
#include <linux/fcntl.h> 
#include <linux/dirent.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/kdev_t.h> 
//定义全局变量
struct file *file = NULL; 
struct inode *inode = NULL; 
struct dentry *dentry = NULL; 
//定义传入的参数
static char *c_path = "/home/tong/Code_3/Ls";
//设置默认值
module_param( c_path, charp, 0644 ); 
//传递命令行参数
MODULE_PARM_DESC( c_path, "char *param!\n" ); 
//对模块的参数进行描述
static int ShowFileInfo( void ); 
static int ShowDirInfo( void ); 
static int OpenFile( char * ); 
//插入模块时初始化调用函数
static __init int path_init( void ) 
{ 
	printk( "-------------------------------------\n" ); 
	printk( "c_path: %s\n", c_path ); 
	OpenFile( c_path ); 
	return 0; 
} 
//移除模块时调用函数
static __exit void path_exit( void ) 
{ 
	printk( "\nOver!\n" ); 
	printk( "-------------------------------------\n" ); 
	return; 
} 
//打印文件信息
static int ShowFileInfo( void ) 
{ 
//通过file获取dentry再获取inode的相关内容
	inode = file->f_dentry->d_inode; 
	printk( "\nShow The Inode Information: \n" ); 
	// 分配给文件的超级块的节点号
	printk( " 1.Inode Number: %ld\n", inode->i_ino ); 
	// 访问控制权限
	printk( " 2.Access Right: %o\n", inode->i_mode ); 
	// 引用计数
	printk( " 3.Reference Count: %d\n", inode->i_count.counter ); 
	// 硬链接数
	printk( " 4.Hard Link Count: %u\n", inode->i_nlink ); 
	// 使用者ID 
	//printk( " 5.User ID: %d\n", inode->i_uid ); 
	// 使用者组ID 
	//printk( " 6.Group ID: %d\n", inode->i_gid ); 
	// 版本号
	printk( " 7.Version: %lu\n", ( long unsigned int )inode->i_version ); 
	// 以字节为单位的文件大小
	printk( " 8.File Size(byte): %d\n", ( int )inode->i_size ); 
	// 文件块数
	printk( " 9.Block Count: %lu\n", (long unsigned int)inode->i_blocks ); 
	// 状态标志
	printk( "10.File State: %ld\n", inode->i_state ); 
	return 0; 
} 
//打印目录信息
static int ShowDirInfo( void ) 
{ 
	dentry = file->f_dentry; 
	printk( "\nShow The Dentry Infomatiom:\n" ); 
	// 目录项对象使用计数器，未使用态0、使用态正整数、负状态负整数
	printk( "1.Directory Count: %d\n", ( int )d_count(dentry) ); 
	//目录项标志
	printk( "2.Dentry Flag: %u\n", dentry->d_flags ); 
	// 哈希表的名字
	printk( "3.Hash Table Number: %u\n", dentry->d_name.hash ); 
	// 目录的名字
	printk( "4.Directory Name: %s\n", dentry->d_name.name ); 
	// 目录名字的长度
	printk( "5.Name Length:%u\n", dentry->d_name.len ); 
	// 存放短文件名
	printk( "6.Short Name: %s\n", dentry->d_iname ); 
	// 时间，被d_revalidate使用
	printk( "7.Time: %lu\n", dentry->d_time ); 
	return 0; 
} 
// 打开文件
static int OpenFile( char *path ) 
{ 
	//以目录的形式打开
	file = filp_open( path, O_DIRECTORY, 0 ); 
	if ( IS_ERR( file ) ) 
	{ 
		// 不成功则以文件形式打开
		file = filp_open( path, O_RDONLY, 0444 ); 
		if ( IS_ERR( file ) ) 
		{ 
			// 路径错误
			printk( "The Paht %s failed!\n", path ); 
			return 0; 
		} 
		// 该路径指向一个文件
		printk( "This is file!\n" ); 
		ShowFileInfo(); 
		filp_close( file, NULL ); 
		return 0; 
	} 
	else 
	{ 
		// 该路径指向一个目录
		printk( "This is diretory!\n" ); 
		ShowDirInfo(); 
		filp_close( file, NULL ); 
		return 0; 
	} 
} 
MODULE_LICENSE( "GPL" ); 
module_init( path_init ); 
module_exit( path_exit ); 


