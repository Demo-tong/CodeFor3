#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globVar=5;

int main ( void )     {
 	pid_t   pid;
 	int        var = 1, i;
  	printf ( "fork is different with vfork \n“ ) ;
	pid = vfork ( );
 	switch ( pid )  {
     	case   -1:  perror ( "process creation failed\n“ );
    	 	   exit(0);
	case  0 :  i = 3;
                    while ( i - - > 0 )   {
                               printf ( "Child process is running\n“ );
                               globVar + +;             var + +;
			     sleep ( 1 ) ;       }
                    printf ( "Child's globVar=%d, var=%d\n", globVar, var );
                    break;
    default :  i = 5;
                    while ( i - ->0 )     {
                                printf ( "Parent process is running\n“ );
                                globVar + +;         var + +;
                                sleep ( 1 ) ;       }
                    printf ( "Parent's globVar=%d, var=%d\n", globVar, var);
                    exit ( 0 );     } 
}
