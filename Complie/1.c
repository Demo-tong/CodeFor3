 #include "init_operater_table.h"
 //#include "init_operater_table.h"

int find_pos(char c)
{
    int i;
    
    for (i = 0 ; i<operater_mark_number ; i++)
        if(operater_mark[i] == c)
            return i;

        return -1;    //这句执行不到
}

void init_operater_table(int size , char * operater_mark_string)
{
    int i;

    operater_mark_number = size;    //初始化算符的个数

    operater_table = (int **)malloc(sizeof(int *) * size);
    for (i = 0 ; i<size ; i++)
        operater_table[i] = (int *)malloc(sizeof(int) * size);

    //////////////////////////////////////////////////////////////////////////
    for (i = 0 ; i<size -1 ; i++)
    {
        operater_table[size-1][i] = LEFT_L_RIGHT;
        operater_table[i][size-1] = LEFT_G_RIGHT;
    }

    operater_table[size-1][size-1] = LEFT_E_RIGHT;
    
    operater_mark = (char *)malloc(sizeof(int) * ( size+1) );
    strcpy(operater_mark , operater_mark_string);
    operater_mark[size - 1] = '#';    //将结束标号存起来
    operater_mark[size] = '\0';    //字符串结尾符

    operater_table[find_pos('(')][find_pos('#')] = 52;
    operater_table[find_pos('#')][find_pos(')')] = 52;

}

void free_operater_table(int size)
{
    int i;

    for (i = 0 ; i<size ; i++)
        free(operater_table[i]);

    free(operater_table);

    free(operater_mark);
}

void make_operater_table_greater(const char * vt_gather , char c)    //第一个参数一个VT集合 第二个参数一个非终结符 （运算符）
{    //左边优先级高
//printf("%s .. %c\n",vt_gather , c);    //test

    int i;
    int length = strlen(vt_gather);
    int c_pos = find_pos(c);

    for (i = 0 ; i<length ; i++)
    {
        operater_table[ find_pos(vt_gather[i]) ][ c_pos ] = LEFT_G_RIGHT;
    }
}

void make_operater_table_less(const char * vt_gather , char c)
{
    //左边优先级低
//printf("%s .. %c\n",vt_gather , c);    //test
    int i;
    int length = strlen(vt_gather);
    int c_pos = find_pos(c);

    for (i = 0 ; i<length ; i++)
    {
        operater_table[ c_pos ][ find_pos(vt_gather[i]) ] = LEFT_L_RIGHT;
    }
}

void make_operater_table_equal(char c1 , char c2)
{
    operater_table[ find_pos(c1) ][ find_pos(c2) ] = LEFT_E_RIGHT;
}

int get_priority(char c1 , char c2)
{
printf("test:%c\n",c1);
    return operater_table[find_pos(c1)][find_pos(c2)];
}

void test()
{
    int i;
    int j;

    for (i = 0 ; i<operater_mark_number ; i++)
    {
        for (j = 0 ; j<operater_mark_number ; j++)
            if (operater_table[i][j] == LEFT_G_RIGHT)
                printf("[%c,%c]>  ",operater_mark[i] , operater_mark[j]);
            else
                if (operater_table[i][j] == LEFT_L_RIGHT)
                    printf("[%c,%c]<  ",operater_mark[i] , operater_mark[j]);
                else
                     if(operater_table[i][j] == LEFT_E_RIGHT)
                         printf("[%c,%c]=  ",operater_mark[i] , operater_mark[j]);
                    else
                        printf("[%c,%c]?  ",operater_mark[i] , operater_mark[j]);
    //        printf("%d ,",operater_table[i][j]); 
        printf("\n");
    }
}
