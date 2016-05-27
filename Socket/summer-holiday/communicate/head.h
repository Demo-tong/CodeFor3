/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月08日 18时38分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sweetheart502, liyingxiao502@gmail.com
 *        Company:  Class 1304 of Software Engineering
 *
 * =====================================================================================
 */


#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>

#define DEBUG 1

#define  PORT 	4507 		//the server's port
#define  LIST 	12 		//the line's length

#define MAX_LEN 500 		//the message's length

//user_info
struct user {
	char username[32];
	char password[32];
	int  state;
	int  socket;
};

//send msg
struct msg {
	char 		from[32]; 			//the sender's name
	char 		to[32]; 			//the receiver's name
	int 		command;  			//the client's command
	char 		content[MAX_LEN]; 		//the client's send_msg
	struct msg 	*next; 				//the next pointer
};

//the login's link
struct  line {
	char 		username[32]; 				//the enter's name
	int 		socket; 				//the enter's socket
	struct line	*next; 					//the next pointer
};


struct line *head;

//display the error and write it to file_error
void my_err ( char *string, int line );

//write the error to the file_error
void record_err ( char *string );

//write the error_func to the file_error
void record_wr ( int fd, char *string );

//write the error_time to the file_error
void record_time ( int fd );

//to accept the request
void process ( int sock_fd );

//to process it in the thread
void *thread_chat ( void *member );

//to register a user
void regist ();

//to log in the system
void login ( int conn_fd );

//void user_login (int conn_fd);

//void link_server (  );


//write the error function's name
void record_wr ( int fd, char *string )
{
	if ( write ( fd, string, strlen (string) ) != strlen (string) ) {
		perror ( "write" );
		exit (1);
	}
}

//write the time to the file
void record_time ( int fd )
{
	time_t 	now;

	time ( &now );

	if ( write ( fd, ctime ( &now ), strlen ( ctime (&now) ) ) != strlen ( ctime (&now) ) ) {
		perror ( "write" );
		exit (1);
	}
}
