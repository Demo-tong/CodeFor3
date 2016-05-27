/*************************************************************************
	> File Name: ls2.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年05月11日 星期三 13时40分14秒
 ************************************************************************/

/*头文件*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<math.h>

/*宏定义*/
#define lenOfName 256
#define maxN 1005
#define maxM 505
#define maxL 105
#define lenOfPath 256<<4
#define LS 0        //ls
#define LS_A 1      //ls -a
#define LS_L 2      //ls -l
#define LS_TMP 3    //ls /tmp
#define LS_U 4
#define LS_T 5      //ls -t

/*函数声明*/
void do_ls(int, char[]);
long doStat(char *);                        /*get file info*/
long show_file_info(char *, struct stat *); //ls -l的输出
void mode_to_letters(int, char[]);          //文件属性:drwxrwxrwx
char *uid_to_name(uid_t);                   //通过uid获得对应的用户名
char *gid_to_name(gid_t);               //通过gid获得对应的组名
void getColor(char *);                  
int get_file_type(char *);              //get file type
int get_modify_time(char *);            //get file last modify time
void getWidth();
int cmp1(const void *, const void *);   //文件名排序
int cmp2(const void *, const void *);   //文件修改时间排序

struct outputFile{
    char FileName[lenOfName];
    int modify_time;
    int visit_time;
    int file_type;
}Output[maxN], OutputPoint[maxM], Temp[maxN + maxM];

int colormode, foreground, background;
int terminalWidth;

/*
 *获取文件信息
 */
long dostat(char *filename){
    struct stat info;       //保存文件的创建时间，大小等信息
    long total_size = 0;

    if(stat(filename, &info) == -1){
        perror(filename);
        printf("filename:%s\n", filename);
    }
    else{
        char *pname = strrchr(filename, '/');       //查找给定文件名中最后出现'/'的位置，并返回其后的文件名(包含'/')
        getColor(filename);
        total_size = show_file_info(pname+1, &info);
    }

    return total_size;
}

/*
 *设置文件模式rwxrwxrwx
 */
void mode_to_letters(int mode, char str[]){
    strcpy(str, "----------");

    if(S_ISDIR(mode))   str[0] = 'd';
    if(S_ISCHR(mode))   str[0] = 'c';
    if(S_ISBLK(mode))   str[0] = 'b';

    if(mode & S_IRUSR)  str[1] = 'r';
    if(mode & S_IWUSR)  str[2] = 'w';
    if(mode & S_IXUSR)  //str[3] = 'x';
    {
        if(mode & S_ISUID)
            str[3] = 's';
        else
            str[3] = 'x';
    }else if(mode & S_ISUID){
        str[3] = 'S';
    }

    if(mode & S_IRGRP)  str[4] = 'r';
    if(mode & S_IWGRP)  str[5] = 'w';
    if(mode & S_IXGRP)  //str[6] = 'x';
    {
        if(mode & S_ISGID)
            str[6] = 's';
        else
            str[6] = 'x';
    }
    else if(mode & S_ISGID){
        str[6] = 'S';
    }

    if(mode & S_IROTH)  str[7] = 'r';
    if(mode & S_IWOTH)  str[8] = 'w';
    if(mode & S_IXOTH) // str[9] = 'x';
    {
        if(mode & S_ISVTX)
            str[9] = 't';
        else
            str[9] = 'x';
    }
    else if(mode & S_ISVTX){
        str[9] = 'T';
    }
    return ;
 }

/*
 *通过uid获得对应的用户名
 */
char *uid_to_name(uid_t uid){
    struct passwd *pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }else{
        return pw_ptr->pw_name;
    }
 }

/*
 * 通过gid获得对应的组名
 */
char *gid_to_name(gid_t gid){
    struct group *grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr, "%d", gid);
        return numstr;
    }else{
        return grp_ptr->gr_name;
    }
}

/*
 *获取文件类型
 */
int get_file_type(char *filename){
    struct stat info;
    stat(filename, &info);
    int file_type = 0;
    file_type = info.st_mode & S_IFMT;
    return file_type;
}

/*
 *获取文件最后修改时间
 */
int get_modify_time(char *filename){
    struct stat info;
    stat(filename, &info);
    int modify_time = 0;
    modify_time = info.st_mtime;

    return modify_time;
 }

/*
 *last visit time
 */
int get_visit_time(char *filename){
    struct stat info;
    stat(filename, &info);
    int visit_time = 0;
    visit_time = info.st_atime;

    return visit_time;
}

/*
 *判断文件是否为目录文件
 */
int isadir(char *str){
    struct stat info;
    return (lstat(str, &info) != -1 && S_ISDIR(info.st_mode));
}

/*
* 获取终端的宽度，默认为80， 若获取失败，将激活-1选项
*/
void getWidth(){
    char *tp;
    struct winsize wbuf;

    terminalWidth = 80;

    /*
     *判断文件描述符是否为终端机
     */
    if(isatty(STDOUT_FILENO)){
        if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &wbuf) == -1 || wbuf.ws_col == 0){
            if(tp = getenv("COLUMNS"))
                terminalWidth = atoi(tp);
        }
        else{
            terminalWidth = wbuf.ws_col;
        }
    }

    return ;
}

/*
 *首字母按照字典顺序排序
 */
int cmp1(const void *p, const void *q){
    char T1[lenOfName], T2[lenOfName];
    strcpy(T1, (*(struct outputFile *)p).FileName);
    strcpy(T2, (*(struct outputFile *)q).FileName);

    return strcasecmp(T1, T2);
}

/*
 *按照文件修改时间进行排序
 */
int cmp2(const void *p, const void *q){
    return (*(struct outputFile *)p).modify_time < (*(struct outputFile *)q).modify_time;    
}


int cmp2_u(const void *p, const void *q){
    return (*(struct outputFile *)p).visit_time < (*(struct outputFile *)q).visit_time;    
}

/*
 *ls -l的输出
 */
long show_file_info(char *filename, struct stat * info_p){
    char modestr[12];
    char b_time[32] ;

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s ", modestr);
    printf("%3d ", (int)info_p->st_nlink);
    printf("%-2s ", uid_to_name(info_p->st_uid));
    printf("%-1s ", gid_to_name(info_p->st_gid));
    printf("%7ld ", (long)info_p->st_size);
    strcpy(b_time , (char *)ctime(&info_p->st_mtime)) ;
    b_time[strlen(b_time)-1] = '\0' ;
    printf ("%.12s ", b_time) ;
    printf("\033[%d;%d;%dm %s \033[0m\n", colormode, foreground, background, filename);

    return (long)info_p->st_size;
}

/*
 *为文件添加输出颜色
 */
void getColor(char *filename){
    struct stat info;

    stat(filename, &info);
    foreground = 1;
    background = 1;
    colormode = 0;

    switch((info.st_mode & S_IFMT)){
        /*regular普通文件*/
        case S_IFREG:
            foreground = 1;
        break;
        /*link链接文件*/
        case S_IFLNK:
            foreground = 36;
            colormode = 1;
        break;
        /*sock*/
        case S_IFSOCK:
            foreground = 35;
            colormode = 1;
        break;
        /*directory目录文件*/
        case S_IFDIR:
            foreground = 34;
        break;
        /*block special块设备文件*/
        case S_IFBLK:
            foreground = 33;
            colormode = 1;
        break;
        /*character special字符设备文件*/
        case S_IFCHR:
            foreground = 33;
            colormode = 1;
        break;
        /*fifo无名管道*/
        case S_IFIFO:
            foreground = 32;
            colormode = 1;
        break;
    }
}

/*
 *ls分栏输出
 */
void display_LS(int cnt){
    int wordLenMax = 0;     //最大长度字符串
    int wordRowNum = 0;     //行数
    int wordColNum = 0;     //列数
    int wordMax[300];

    memset(wordMax, 0, sizeof(wordMax));

    int i, j, k;

    for(i = 0; i < cnt; i++){
        if(i == 0)
            wordLenMax = strlen(Output[i].FileName);
        else{
            wordLenMax = wordLenMax > strlen(Output[i].FileName) ? wordLenMax : strlen(Output[i].FileName);
        }
    }

    //计算要分的栏数及行数
    wordRowNum = terminalWidth / wordLenMax;
    //printf("max:%d  %d\n", wordLenMax, wordRowNum);
    if(cnt % wordRowNum == 0)
        wordColNum = cnt / wordRowNum;
    else
        wordColNum = cnt / wordRowNum + 1;
    //printf("col:%d\n", wordColNum);
    for(i = 0; i < cnt; i += wordColNum){
        k = i / wordColNum;
        for(j = i; j < (i+wordColNum); j++){
            wordMax[k] = wordMax[k] > strlen(Output[j].FileName) ? wordMax[k] : strlen(Output[j].FileName);
        }
    }

    //输出
    for(i = 0; i < wordColNum; i++){
        j = i;
        while(j < cnt){
            getColor(Output[j].FileName);
            printf("\033[%d;%d;%dm%-10s \033[0m", colormode, foreground, background, Output[j].FileName);
            for(k = strlen(Output[j].FileName); k < wordMax[j/wordColNum]; k++)
                printf(" ");
            j += wordColNum;
        }
        printf("\n");
    }

    return ;
 }

/*
 *ls -a分栏输出
 */

void display_LS_a(int cntPoint, int cnt){
    int CNT = 0;
    int wordLenMax = 0;     //最大长度字符串
    int wordRowNum = 0;     //行数
    int wordColNum = 0;     //列数
    int i, j;

    /*
     *取得最大文件名的长度，根据文件名长度对列出的文件进行分栏
     */
    for(i = 0; i < cntPoint; i++){
        strcpy(Temp[CNT].FileName, OutputPoint[i].FileName);
        Temp[CNT].file_type = OutputPoint[i].file_type;
        Temp[CNT].modify_time = OutputPoint[i].modify_time;
        CNT++;
        wordLenMax = wordLenMax > strlen(OutputPoint[i].FileName) ? wordLenMax : strlen(OutputPoint[i].FileName);
    }
    for(i = 0; i < cnt; i++){
        strcpy(Temp[CNT].FileName, Output[i].FileName);
        Temp[CNT].file_type = Output[i].file_type;
        Temp[CNT].modify_time = Output[i].modify_time;
        CNT++;
        wordLenMax = wordLenMax > strlen(Output[i].FileName) ? wordLenMax : strlen(Output[i].FileName);
    }

    wordLenMax += 2;
    wordRowNum = terminalWidth / wordLenMax;
    if(CNT % wordRowNum == 0)   wordColNum = CNT / wordRowNum;
    else    wordColNum = CNT / wordRowNum + 1;

    for(i = 0; i < wordColNum; i++){
        j = i;
        while(j < CNT){
            getColor(Temp[j].FileName);
            printf("\033[%d;%d;%dm%-19s \033[0m", colormode, foreground, background, Temp[j].FileName);
            j += wordColNum;
        }
        printf("\n");
    }

    printf("Total: %d\n", CNT);
    return ;
 }

/*
 *ls /tmp分栏输出
 */
void display_LS_tmp(int cnt){
    display_LS(cnt);
    return ;
 }

/*
 *具体处理函数
 */
void do_ls(int myJudge, char myOrder[]){
    char dirname[maxL];

   /*if(myJudge != LS_TMP && myJudge != LS_L){
        strcpy(dirname, ".");
    }*/
    
    if(myJudge != LS_TMP){
        strcpy(dirname, "./");
    }
    else{
        strcpy(dirname, myOrder);
    }

    DIR *dir_ptr;
    struct dirent *direntp;
    int cntOutput = 0;
    int cntOutputPoint = 0;
    char full_path[256];

    if((dir_ptr = opendir(dirname)) == NULL){//打开目录文件失败
        fprintf(stderr,"cannot open %s\n", dirname);
    }
    else{
        if(myJudge != LS_L){
            while((direntp = readdir(dir_ptr)) != NULL){
               if(direntp->d_name[0] == '.'){
                    //隐藏文件
                    strcpy(OutputPoint[cntOutputPoint].FileName, direntp->d_name);
                    OutputPoint[cntOutputPoint].file_type = get_file_type(OutputPoint[cntOutputPoint].FileName);
                    OutputPoint[cntOutputPoint].modify_time = get_modify_time(OutputPoint[cntOutputPoint].FileName);
                    OutputPoint[cntOutputPoint].visit_time = get_visit_time(OutputPoint[cntOutputPoint].FileName);
                    cntOutputPoint++;
                }
                else{
                    strcpy(Output[cntOutput].FileName, direntp->d_name);
                    Output[cntOutput].file_type = get_file_type(Output[cntOutput].FileName);
                    Output[cntOutput].modify_time = get_modify_time(Output[cntOutput].FileName);
                    Output[cntOutput].visit_time = get_visit_time(Output[cntOutput].FileName);
                    cntOutput++;
                }
            }
        }

        /*
         *若为ls -t则按照文件修改时间排序，否则按照文件大小排序
         */
        if(myJudge == LS_T){
            qsort(OutputPoint, cntOutputPoint, sizeof(OutputPoint[0]), cmp2);
            qsort(Output, cntOutput, sizeof(Output[0]), cmp2);
        }else if(myJudge == LS_U){
            qsort(OutputPoint, cntOutputPoint, sizeof(OutputPoint[0]), cmp2_u);
            qsort(Output, cntOutput, sizeof(Output[0]), cmp2_u);
        }else{
            qsort(OutputPoint, cntOutputPoint, sizeof(OutputPoint[0]), cmp1);
            qsort(Output, cntOutput, sizeof(Output[0]), cmp1);
        }

        /*
         *ls && ls -t
         */
        if(myJudge == LS || myJudge == LS_T || myJudge == LS_U){
            display_LS(cntOutput);
            printf("Total: %d\n", cntOutput);
            closedir(dir_ptr);
        }
        /*
         *ls -a
         */
        else if(myJudge == LS_A){
            display_LS_a(cntOutputPoint, cntOutput);
            closedir(dir_ptr);
        }
        /*
         *ls -l
         */
        else if(myJudge == LS_L){
            while((direntp = readdir(dir_ptr)) != NULL){
                if(direntp->d_name[0] == '.'){
                        strcpy(OutputPoint[cntOutputPoint].FileName, direntp->d_name);
                        OutputPoint[cntOutputPoint].file_type = get_file_type(OutputPoint[cntOutputPoint].FileName);
                        OutputPoint[cntOutputPoint].modify_time = get_modify_time(OutputPoint[cntOutputPoint].FileName);
                        OutputPoint[cntOutputPoint].visit_time = get_visit_time(OutputPoint[cntOutputPoint].FileName);
                        cntOutputPoint++;
                    }else{
                        strcpy(full_path, dirname);
                        int dir_len = strlen(dirname);
                        strcpy(full_path + dir_len, direntp->d_name);
                        strcpy(Output[cntOutput].FileName, full_path);
                        Output[cntOutput].file_type = get_file_type(Output[cntOutput].FileName);
                        Output[cntOutput].modify_time = get_modify_time(Output[cntOutput].FileName);
                        Output[cntOutput].visit_time = get_visit_time(Output[cntOutput].FileName);
                        cntOutput++;
                    }
            }

            qsort(OutputPoint, cntOutputPoint, sizeof(OutputPoint[0]), cmp1);
            qsort(Output, cntOutput, sizeof(Output[0]), cmp1);
            
            int i;
            long sum_size = 0;
            for(i = 0; i < cntOutput; i++){
                sum_size += dostat(Output[i].FileName);
            }
            //sum_size = (sum_size % 1024) ? sum_size/1024+1 : sum_size/1024;
            closedir(dir_ptr);
            printf("Total: %d\n", cntOutput);
            printf("总用量：%ld\n", sum_size/1024);
        }
        /*
         *ls /tmp
         */
        else{
            display_LS_tmp(cntOutput);
            printf("Total: %d\n", cntOutput);
            closedir(dir_ptr);
        }
    }

    return ;
}

/*主函数*/
int main(int argc, char *argv[]){
    getWidth();

    int i;

    if(argc == 1){
        do_ls(LS, "ls");
    }else{
        int ord;

        //getopt用来解析命令行选项参数
        while((ord = getopt(argc, argv, ":latu")) != -1){
            switch(ord){
                case 'a':
                    do_ls(LS_A, "ls-a");
                break;
                case 'l':{
                    if(argc == 2)   do_ls(LS_L, "/");
                    else{
                        for(i = 1; i < argc; i++){
                            if(argv[i][0] == '-')   continue;
                            printf("%s:\n", argv[i]);
                            do_ls(LS_L, argv[i]);
                        }
                    }
                    return 0;
                }
                break;
                case 't':
                    do_ls(LS_T, "ls-t");
                break;
                case 'u':
                    do_ls(LS_U, "ls-u");
                break;
                default:
                break;
            }
        }
        for(i = 1; i < argc; i++){
            if(argv[i][0] == '-')   continue;
            printf("%s:\n", argv[i]);
            do_ls(LS_TMP, argv[i]);
        }
    }

    return 0;
}
