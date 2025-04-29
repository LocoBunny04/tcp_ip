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
void err_msg(char *);
int ls_fd = -1; /* Listening socket descriptor */
int rs_fd = -1; /* Receive socket descriptor */
int outf_fd = -1; /* Output file descriptor */

void cleanup(void) {
    /* free buffer if needed */
    if( in_buf != NULL ) {
        free( in_buf );
        in_buf = NULL;
    }

    /* close listening socket if needed */
    if( ls_fd >= 0 ) {
        close( ls_fd );
        ls_fd = -1;
    }

    /* close receiving socket if needed */
    if( rs_fd >= 0 ) {
        close( rs_fd );
        rs_fd = -1;
    }

    /* close output file if needed */
    if( of_fd >= 0 ) {
        close( of_fd );
        of_fd = -1;
    }

    /* missing Goodbye! message */
    printf( "server: Goodbye!\n" );

}

/* Signal handler for SIGINT (via [CTRL]+[C]) */
void SIGINT_handler( int sig ) {

    /* Maybe issue a message */
    fprintf( stderr, "Server interrupted.  It will now be terminated.\n" );
  
    cleanup();
 
    /* Terminate the program... for 'reals' this time. */
    exit( EXIT_FAILURE );
 
} /* end SIGINT_handler() */

 /* Error message */
void err_msg(char, *msg){
    fprintf(stderr, msg);
    cleanup();
    exit(EXIT_FAILURE);
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
    * optional enable so_resuseport
    * initialize server address structure
    * retry binding if port is in use
    * listen on socket
    * accept client connection
    * receive data from client (generate uniq file name)
    * write data to file
    * allocate buffer for each file transfer individually
    * receive data from client
    * check for receive errors
    * cleanup
    */

    unsigned short port;
    char *endptr;
    int opt = 1;
    /* listening socket internet address */
    struct in_addr ls_ia;
    /* listening socket socket address */
    struct sockaddr_in ls_sa;
    struct server_addr, client_addr;

    if (argc != 2){
        err_msg("server: Usage server <listen_Port>\n");
    }

    /* Port */
    port = (unsigned short int) atoi(argv[1]); /* Parsing port input to a number using atoi to convert string to number */
    /* Check if the input for the port number is valid and within the acceptable range */
    if (*endptr != '\0' || port < 0 || port > 65535 || (port >= 0 && port <= 1023)) {
        if (server_port < 0 || server_port > 65535) {
            err_msg("server: Error: Invalid port number.\n");
        } else {
            err_msg("server: ERROR: Port number is privileged.\n");
        }
    }

    /* signal handler */
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, SIG_IGN); /* Ignore SIGPIPE to handle disconnections */

    /* set up socket*/
    ls_ia.s_addr = inet_addr( "127.0.0.1" );
    ls_sa.sin_family = AF_INET;
    ls_sa.sin_addr = ls_ia;
    ls_sa.sin_port = htons( port );

    /* Create TCP socket */
    ls_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(ls_fd < 0){
        perror("server: Error: Failed to create socket\n");
        return(EXIT_FAILURE);
    }

    /* Making listening socket reusable */
    if(setsockopt(ls_fd, SQL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) <0){
        err_msg("Server: ERROR: Failed to set SO_REUSEADDR option");
    }
    
    /* Making SO_REUSEPORT optional */
    if(setsockopt(ls_fd, SQL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0){
        fprintf("server: ERROR: Failed to set SO_REUSEPORT option\n");
        cleanup();
        return(EXIT_FAILURE);
    }

    /* reset server address structure */
    memset(&rs_fd, 0, sizeof(ls_fd));

    if( bind( ls_fd, (struct sockaddr *) &ls_sa, sizeof( ls_sa ) ) != 0 ) {
        /* print bind error and exit */
        fprintf(stderr, "server: ERROR: Failed to bind socket.\n" );
        cleanup();
        return(EXIT_FAILURE);
    }
    /* Listening for incoming connections */
    if(listen(ls_fd, BACKLOG) < 0){
        fprintf(stderr, "server: ERROR: listen(): Failed.\n");
        cleanup();
        return(EXIT_FAILURE);
    }

    /* Server Loop */
    while(1){
        /* receive socket socket address */
        struct sockaddr_in rs_sa;
        /* receive socket socket address size */
        socklen_t rs_sa_size = sizeof( rs_sa );
        /* bytes received counter */
        int bytes_received;
        printf("server: Awaiting TCP connections on port %d ... \n", port);

    }

}
