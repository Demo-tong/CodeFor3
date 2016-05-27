/*************************************************************************
	> File Name: file.c
	> Author: FlowerTong 
	> Mail: 1051165644@qq.com 
	> Created Time: 2015年12月29日 星期二 19时52分24秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

main()     
{	
      char str[][15]={"January","February","March","April","May", "June",
            "July","August","september","October","November","December"};
      char out[12][15];	
      FILE *fp;	
      int i;	

    fp=fopen("strtext.txt","w");	
    if(fp==NULL){		
        printf("cant open file!\n");		
        exit(1);	
    }	
    fwrite(str,15,12,fp);	
    fclose(fp);        
    printf("write data success!\n");	
    
    fp=fopen("strtext.txt","r");	
    if(fp==NULL){		
        printf("cant open file!\n");		
        exit(1);	
    }	
    fread(out,15,12,fp);	
    fclose(fp);	
    printf("read data success!\n");        
    
    printf("the data in array out are:\n");	
    for(i=0;i<12;i++)		
        printf("%s\n",out[i]);
}

