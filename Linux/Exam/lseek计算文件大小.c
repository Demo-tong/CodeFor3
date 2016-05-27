#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int my_callen ( int fd )     {
   int len;  
   if ( lseek( fd , 0 , SEEK_END ) == -1 ) 
         perror( "lseek“);
   if ( ( len = lseek ( fd , 0 , SEEK_CUR ) ) == -1 )            
         perror( "lseek“); 
   return len;
}
int main ( int argc , char ** argv )   {
   int len = -1;
   int fd;
   if ( argc < 2 )  
         perror ( "para“) ; 
   if ( ( fd = open ( argv[1] , O_RDONLY ) ) ==-1 )    {
         perror ( "open“) ;  exit(EXIT_FAILURE);      }
   len = my_callen ( fd ) ;  
   close(fd); 
   if(len<0)    perror ( "cal“) ;
   else
         printf ( "There are %d bytes in file %s!\n“ , len , argv[1] ); 
   return 0; 
}
