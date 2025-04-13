/*
 * Auth: Kawinthida Haase
 * Date: 04-12-2025  (Due: 05-04-2025)
 * Course: CSCI-3550 (Sec: 001)
 * Desc: /*
 * Auth: Kawinthida Haase
 * Date: 04-12-2025  (Due: 05-04-2025)
 * Course: CSCI-3550 (Sec: 001)
 * Desc: This is a TCP/IP client program that connects to a server and sends a file.
*/

#include <stdio.h>    /* For printf, fprintf*/
#include <stdlib.h>   /* For exit, EXIT_FAILURE*/
#include <fcntl.h>    /* For open(), O_RDONLY, O_WRONLY, O_CREAT */
#include <unistd.h>   /* For read(), write(), close() */
#include <string.h>   /* For strlen() */
#include <signal.h>   /* Needed for signal() function */
#include <sys/socket.h> /* For socket(), connect(), send(), recv() */
#include <netinet/in.h> /* For sockaddr_in */
#include <arpa/inet.h> /* For inet_addr() */
#include <errno.h> /* For error no. def */

#define BUFFER_SIZE (10 * 1024 * 1024) /* 10 MB buffer size */

/* Global Variables */
char *buffer = NULL; /* Buffer to hold data */
int curr_sock_fd = -1; /* Current Socket file descriptor */
int curr_fd = -1; /* Current File descriptor */

/* Function Prototypes */
void cleanup(void);
void signal_handler(int sig);

void cleanup(void) {
    /* Proper release memory */
    if (buffer != NULL) {
        free(buffer);       /* Release it */
        buffer = NULL;      
    } 
    /* Closes socket */
    if (curr_sock_fd >= 0) {
        close(curr_sock_fd); /* Close the socket connection */
        curr_sock_fd = -1;   /* reset socket descriptor */  
    } 
    /* Close the output file */
    if (curr_fd >= 0) {
        close(curr_fd);   /* Close the file */
        curr_fd = -1;     /* reset file descriptor */
    }
}

/* SIGINT handler for client (e.g., Ctrl+C) */
void signal_handler(int sig) {
    /* Issue an error */
    fprintf(stderr, "client: Client interrupted. Shutting down.\n");
    /* Cleanup after yourself */
    cleanup();
    /* Exits for 'reals' */
    exit(EXIT_FAILURE); /* end SIGINT handler() */
}

int main(int argc, char *argv[]) {
    /* 
     * server ip, endptr, server port, loop variable
     * argument checking
     * server setting
     * signal 
     * buffer allocate
     * File Transfer Loop
     * socket create
     * initialize server address struct
     * connect to server
     * check file exist and permissions
     *   * open file
     *       * read file and send to server
     * check file read errors
     * close file
     *   * close socket
     * cleanup
    */

    /* Variables */
    char *server_ip = NULL; /* Server IP */
    char *endptr = NULL; /* End pointer */
    int server_port; /* Server Port */
    int i = 0; /* Loop variable */

    /* Check for the correct number of arguments */
    if (argc < 4) {
        fprintf(stderr, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n");
        return EXIT_FAILURE; /* Return error code */
    }

    server_ip = argv[1]; /* Server IP */
    server_port = strtol(argv[2], &endptr, 10); /* Server Port, convert a string to a long integer */

    /* Check if the input for the port number is valid and within the acceptable range */
    if (*endptr != '\0' || server_port < 0 || server_port > 65535 || (server_port >= 0 && server_port <= 1023)) {
        if (server_port < 0 || server_port > 65535) {
            fprintf(stderr, "client: Error: Invalid port number.\n");
        } else {
            fprintf(stderr, "client: ERROR: Port number is privileged.\n");
        }
        return EXIT_FAILURE; /* Return error code */
    }

    /* Register signal handler */
    signal(SIGINT, signal_handler);

    /* Allocate single buffer for each file transfer individually */
    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("client: ERROR: Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    /* Loop through each file */
    for (i = 3; i < argc; i++) {
        const char *file_name = argv[i]; /* File name */
        struct sockaddr_in server_addr; /* Server address */
        ssize_t bytes_read, bytes_sent; 

        /* Message to indicate attempt to connect to server */
        fprintf(stdout, "client: Connecting to %s:%d...\n", server_ip, server_port);

        /* Create a TCP socket */
        curr_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (curr_sock_fd < 0) {
            perror("client: ERROR: Failed to create socket.\n");
            cleanup();
            return EXIT_FAILURE;
        }

        /* Initialize server address structure */
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);
        inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

        /* Connect to server */
        if (connect(curr_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("client: ERROR: Failed to connect to server.\n");
            cleanup();
            return EXIT_FAILURE;
        }

        /* Check if file exists and has read permissions */
        curr_fd = open(file_name, O_RDONLY);
        if (curr_fd < 0) {
            perror("client: ERROR: Failed to open file.\n");
            cleanup();
            return EXIT_FAILURE;
        }

        /* Read file and send to server */
        while ((bytes_read = read(curr_fd, buffer, BUFFER_SIZE)) > 0) {
            bytes_sent = send(curr_sock_fd, buffer, bytes_read, 0);
            if (bytes_sent < 0) {
                perror("client: ERROR: Failed to send data to server.\n");
                cleanup();
                return EXIT_FAILURE;
            }
        }

        /* Check for file read errors */
        if (bytes_read < 0) {
            perror("client: ERROR: Failed to read file.\n");
            cleanup();
            return EXIT_FAILURE;
        }

        /* Close file */
        close(curr_fd);
        curr_fd = -1;

        /* Close socket */
        close(curr_sock_fd);
        curr_sock_fd = -1;
    }

    /* Cleanup after yourself */
    cleanup();

    return EXIT_SUCCESS;
}
*/

#include <stdio.h>    /* For printf, fprintf*/
#include <stdlib.h>   /* For exit, EXIT_FAILURE*/
#include <fcntl.h>    /* For open(), O_RDONLY, O_WRONLY, O_CREAT */
#include <unistd.h>   /* For read(), write(), close() */
#include <string.h>   /* For strlen() */
#include <signal.h>   /* Needed for signal() function */
#include <sys/socket.h> /* For socket(), connect(), send(), recv() */
#include <netinet/in.h> /* For sockaddr_in */
#include <arpa/inet.h> /* For inet_addr() */
#include <errno.h> /* For error no. def */

#define BUFF_SIZE = ((10) * (1024) * (1024)) /* 10 MB  buffer size */

/* Global Variables */
char *buffer = NULL; /* Buffer to hold data */
int curr_sock_fd = -1; /* Current Socket file descriptor */
int curr_fd = -1; /* Current File descriptor */

/* Function Prototypes */
void cleanup(void);
void signal_handler(int sig);

void cleanup(void) {
    /* Proper release memory */
    if( buffer != NULL ){
        free(buffer);       /* Release it */
        buffer = NULL;      
    } 
    /* Closes socket */
    if( curr_sock_fd >= 0){
        close(curr_sock_fd); /* Close the socket connection */
        curr_sock_fd = -1;   /* reset socket descriptor */  
    } 
    /* Close the output file */
    if( curr_fd >= 0 ){
        close(curr_fd);   /* Close the file */
        curr_fd = -1;     /* reset file descriptot */
    }
}
/* SIGINT hander for client (e.g., Ctrl+C) */
void signal_handler(int sig) {
    /* Issue an error */
    fprintf( stderr, "client: Client interupted. Shutting down.\n");
    /* Cleanup after yourself */
    cleanup();
    /* Exits for 'reals' */
    exit( EXIT_FAILURE ); /* end SIGINT handler() */
}
int main(int argc, char *argv[]){
 /* 
  //server ip, endptr, server port, loop variable
  // arguement checking
  //server setting
  //signal 
  //buffer allocate
  //File Transfer Loop
 * socket create
 * initalize server add struct
 * connect to server
 * check file exist and permissions
    * open file
        * read file and send to server
 * check file read errors
 * close file
    * close socket
 * cleanup
*/ 
/* Variables */
    char *server_ip = NULL; /* Server IP */
    char *endptr = NULL; /* End pointer */
    int server_port; /* Server Port */
    int i = 0; /* Loop variable */

    /* Check for the correct number of arguments */
    if (argc < 4) {
        fprintf(stderr, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n");
        return EXIT_FAILURE;/* Return error code */
    }
    server_ip = argv[1]; /* Server IP */
    server_port = strtol(argv[2], &endptr, 10); /* Server Port, convert a string to a long integer */
    /* Check if the input for the port number is valid and within the acceptable range */
    if (*endptr != '\0' || server_port < 0 || server_port > 65535 || (server_port >= 0 && server_port <= 1023)) {
        if (server_port < 0 || server_port > 65535) {
            fprintf(stderr, "client: Error: Invalid port number.\n");
        } else {
            fprintf(stderr, "client: ERROR: Port number is privileged.\n");
        }
        return EXIT_FAILURE; /* Return error code */
    }
    /* Register signal handler */
    signal(SIGINT, signal_handler);

    /* Allocate single buffer for each file transfer individually */
    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        peeror(stderr, "client: ERROR: Failed to allocate memory.\n");
        return(EXIT_FAILURE);
    }

    /* Loop through each file */
    for (i = 3; i < argc; i++) {
        const char *file_name = argv[i]; /* File name */
        struct sockaddr_in server_addr; /* Server address */
        ssize_t  bytes_read, bytes_sent; 
        /* Message to indicate attept to connect to server */
        fprintf(stdout, "client: Connecting to %s:%ld...\n", server_ip, server_port);

        /* Create a TCP socket */
        curr_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (curr_sock_fd < 0) {
            perror("client: ERROR: Failed to create socket.\n");
            cleanup();
            return EXIT_FAILURE;
        }
        /* Initialize server address structure */
        

}/* End of main() */