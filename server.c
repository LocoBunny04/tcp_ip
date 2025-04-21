/*
 * Auth: Kawinthida Haase
 * Date: 04-16-2025  (Due: 05-04-2025)
 * Course: CSCI-3550 (Sec: 001)
 * Desc: /*
 * Auth: Kawinthida Haase
 * Date: 04-12-2025  (Due: 05-04-2025)
 * Course: CSCI-3550 (Sec: 001)
 * Desc: This is a TCP/IP server program that recieves files.
*/

#include <stdio.h>    /* For printf, fprintf */
#include <stdlib.h>   /* For exit, EXIT_FAILURE */
#include <fcntl.h>    /* For open(), O_RDONLY, O_WRONLY, O_CREAT */
#include <unistd.h>   /* POSIX system calls */
#include <string.h>   /* For strlen() */
#include <signal.h>   /* Needed for signal() function */
#include <arpa/inet.h> /* For inet_addr() */
#include <errno.h> /* For error no. def */
#include <sys/socket.h> /* For socket(), bind(), listen(), accept() */

#define BACKLOG_SIZE 32 /* Maximum number of connections */
#define BUFFER_SIZE (10 * 1024 * 1024) /* 10 MB buffer size */
#define FILE_Name_LEN (20) /* File name length */


/* Global Variables */
void cleanup(void);
void signal_handler(int sig);
int ls_fd = -1; /* Listening socket descriptor */
int rs_fd = -1; /* Receive socket descriptor */
int outf_fd = -1; /* Output file descriptor */

void cleanup(void) {
    /* Proper release memory */
    if (client)
}
void signal_handler(int sig) {
    /* Issue an error */
    
}

/* Main*/

int main(int argc, char *argv[]) {
    /* To do 
    * declare global variables
    * socket, server address, client address, file descriptor, buffer
    * cleanup function
    * sigint handler
    * argument checking
    * validate port 
    * register signal handler
    * create tcp socket
    * so_reuseaddr socket option
    optional enable so_resuseport
    * initialize server address structure
    * retry binding if port is in use
    * listen on socket
    * accept client connection
    * receive data from client (generate uniq file name)
    * write data to file
    * allocate buffer for each file transfer individually
    receive data from client
    * check for receive errors
    * cleanup

    */
}