/*************************************************************************
	> File Name: wordanalys.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2016年03月28日 星期一 22时02分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//全局变量,循环变量
int i;


/*首先判断字符串是否为算符sizeof，是则输出并返回
 *否则与文件中保存的保留字进行比较，是则输出并返回
 *否则为标识符
 * */
char Judge_Identifier(char *token, int count, char ch){
    FILE *fp;
    i = 0;
    char tmp[100];
    

    while(isalpha(ch) || isdigit(ch) || ch == '_'){
        token[i++] = ch;
        ch = getchar();
    }
    token[i] = '\0';

    if((fp = fopen("keyword.txt", "r")) == NULL){
        printf("keyword.txt 文件打开失败！\n");
        exit(0);
    }
    while(fscanf(fp, "%s", tmp) != EOF){
        if(strcmp(token, tmp) == 0){
            printf("\t\t\t(%d, \t%s)\n", count, token);
            fclose(fp);
            return ch;
        }
    }
    fclose(fp);

    printf("\t\t\t(%d, \t%s)\n", count + 1, token);
    return ch;
}

/*
*分析字符串是否为数字若数字中有一个'.'则为实数
*若一个数字中出现字母、两个或以上'.'则提示出错并返回
*否则为整数
* */
char Judge_Digit(char *token, int count, char ch){

    i = 0;

    while(isdigit(ch)){
        token[i++] = ch;
        ch = getchar();
    }

    if(ch == '.'){//若出现字符不是数字且为'.'时，将其加入到token数组中，并读入下一个字符
        token[i++] = ch;
        ch = getchar();
        
        //读入的字符时数字则继续读入并判断，否则跳出该层if语句进行判断
        if(isdigit(ch) || isalpha(ch) || ch == '.' || ch == '_'){
            
            while(isdigit(ch)){
                token[i++] = ch;
                ch = getchar();
            }
            
            if(isalpha(ch) || ch == '.' || ch == '_'){
                while(isdigit(ch) || isalpha(ch) || ch == '.' || ch == '_'){
                    token[i++] = ch;
                    ch = getchar();
                }
                token[i] = '\0';
                printf("\t标识错误:\t\t\t(%s)\n", token);
            }else{
                token[i] = '\0';
                printf("\t\t\t(%d, \t%s)\n", count, token);
            }
        }
    }else if(isalpha(ch) || ch == '.' || ch == '_'){
        
        while(isdigit(ch) || isalpha(ch) || ch == '.' || ch == '_'){
            token[i++] = ch;
            ch = getchar();
        }
        
        token[i] = '\0';
        printf("\t标识错误:\t\t\t(%s)\n", token);
    }else{
        
        token[i] = '\0';
        printf("\t\t\t(%d, \t%s)\n", count, token);
    }

    return ch;
}


/*
*注释分析部分（//和'/'*）
*否则为除法运算
* */
char Judge_Comment(char *token, int count, char ch){
    i = 0;

    token[i++] = ch;
    ch = getchar();

    if(ch == '/'){//判断"//"型注释
        
        while(ch != '\n' && ch != EOF){
            token[i++] = ch;
            ch = getchar();
        }

        token[i] = '\0';
        printf("\t\t\t(%d, \t%s)\n", count, token);
        
    }else if(ch == '*'){//判断/×型注释

        while(!(token[i-1] == '*' && ch == '/' && i > 1) && ch != EOF){

            token[i++] = ch;
            ch = getchar();
        }
        if(ch != EOF){

            token[i++] = ch;
            ch = getchar();
        }

        token[i] = '\0';
        printf("\t\t\t(%d, \t%s)\n", count, token);
    }else{
        //判断除法运算符
        
        token[i++] = ch;
        ch = getchar();
        
        if(isdigit(ch) || ch == ' '){
            token[i++] = ch;
            ch = getchar();

            while(isdigit(ch)){
                token[i++] = ch;
                ch = getchar();
            }
            token[i] ='\0';
            count = 5;
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }

        else{
            while(ch != '\n'){
                token[i++] = ch;
                ch = getchar();
            }

            token[i] = '\0';
            printf("\t无法判别错误:\t(%s)\n", token);
        }
    }

    return ch;
}


/*
*分析其他字符
*包括算数运算符，逻辑运算符，界符
* */
char Judge_Other(char *token, int count, char ch){
    i = 0;
    

    if(ch == '+'){
        token[i++] = ch;
        ch = getchar();

        if(ch == '+'){
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }else{
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }
    }else if(ch == '-'){
        token[i++] = ch;
        ch = getchar();

        if(ch == '-'){
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }else{
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }
    }else if(ch == '*'){
        
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
	printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '%'){
	
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '&'){
        token[i++] = ch;
        ch = getchar();
        
        if(ch == '&'){
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }else{
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }
    }else if(ch == '|'){
	    token[i++] = ch;
        ch = getchar();
        
        if(ch == '|'){
        
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        
        }else{
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }
    }else if(ch == '!'){
	token[i++] = ch;
        ch = getchar();
        
        if(ch == '='){
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }else{
            token[i] = '\0';
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }
    }else if(ch == '~'){

        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == ','){
    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == ';'){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '('){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token); 
    
    }else if(ch == ')'){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '['){
    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == ']'){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '{'){
    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token); 
    
    }else if(ch == '}'){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 6;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    
    }else if(ch == '='){
    
        token[i++] = ch;
        ch = getchar();
        if(ch == '='){
            token[i++] = ch;
            ch = getchar();
            token[i] = '\0';
            count = 5;
            printf("\t\t\t(%d, \t%s)\n", count, token);
        }else{
            token[i] = '\0';
            count = 5;
            printf("\t\t\t(%d, \t%s)\n", count, token);
        
    }}else if(ch == '#'){
	    
        token[i++] = ch;
        ch = getchar();
        token[i] = '\0';
        count = 0;
        printf("\t\t\t(%d, \t%s)\n", count, token);
    }else{
        while(!(ch == ' ' || ch == '\t' || ch == '\n') && ch != EOF){
            token[i++] = ch;
            ch = getchar();
        }

        token[i] = '\0';
        printf("\t无法识别错误:\t(%s)\n", token);
    }

    return ch;
}

/*
 *主函数：输入需要的字符串并调用子函数
 * */

int main( void ){
    char token[1024] = {'0'}, ch;
    int count;//字符编码
    i = 0;

    //输入重定向
    freopen("in.txt", "r", stdin);
    ch = getchar();
    

    while(ch != EOF){
        
        while((ch == ' '|| ch == '\n' || ch == '\t') && ch != EOF){
            ch = getchar();
        }
        
        //如果第一个字符是字母，则进行标识符判断
        if(isalpha(ch)){
            count = 1;
            ch = Judge_Identifier(token, count, ch);
        }else if(isdigit(ch)){//第一个字符是数字 则进行数组判断
            
            count = 3;
            ch = Judge_Digit(token, count, ch);
        }else if(ch == '/'){//第一个字符是/，则进行注释判断
            
            count = 4;
            ch = Judge_Comment(token, count, ch);
        }else{//其他
            count = 5;
            ch = Judge_Other(token, count, ch);
        }
    }
}
