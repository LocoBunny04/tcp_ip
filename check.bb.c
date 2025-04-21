// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <string.h>
// #include <signal.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <errno.h>

// #define BUFFER_SIZE (10 * 1024 * 1024) /* 10 MB buffer size */

// /* Global Variables */
// char *buffer = NULL; /* Buffer to hold data */
// int curr_sock_fd = -1; /* Current Socket file descriptor */

// /* Function Prototypes */
// void cleanup(void);
// void signal_handler(int sig);

// void cleanup(void) {
//     if (buffer != NULL) {
//         free(buffer);
//         buffer = NULL;
//     }
//     if (curr_sock_fd >= 0) {
//         close(curr_sock_fd);
//         curr_sock_fd = -1;
//     }
// }

// void signal_handler(int sig) {
//     fprintf(stderr, "client: Client interrupted. Shutting down.\n");
//     cleanup();
//     exit(EXIT_FAILURE);
// }

// int main(int argc, char *argv[]) {
//     char *server_ip = NULL;
//     char *endptr = NULL;
//     int server_port;
//     int i = 0;
//     ssize_t bytes_read, bytes_sent;
//     struct sockaddr_in server_addr;

//     if (argc < 4) {
//         fprintf(stderr, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n");
//         return EXIT_FAILURE;
//     }

//     server_ip = argv[1];
//     server_port = strtol(argv[2], &endptr, 10);

//     if (*endptr != '\0' || server_port < 0 || server_port > 65535) {
//         fprintf(stderr, "client: ERROR: Invalid port number.\n");
//         return EXIT_FAILURE;
//     }

//     signal(SIGINT, signal_handler);

//     buffer = (char *)malloc(BUFFER_SIZE);
//     if (buffer == NULL) {
//         perror("client: ERROR: Failed to allocate memory.");
//         return EXIT_FAILURE;
//     }

//     for (i = 3; i < argc; i++) {
//         const char *file_name = argv[i];
//         ssize_t total_bytes_sent = 0;

//         fprintf(stdout, "client: Connecting to %s:%d...\n", server_ip, server_port);

//         curr_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
//         if (curr_sock_fd < 0) {
//             perror("client: ERROR: Failed to create socket.");
//             cleanup();
//             return EXIT_FAILURE;
//         }

//         memset(&server_addr, 0, sizeof(server_addr));
//         server_addr.sin_family = AF_INET;
//         server_addr.sin_port = htons((unsigned short)server_port);

//         if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
//             perror("client: ERROR: Invalid server IP address.");
//             cleanup();
//             return EXIT_FAILURE;
//         }

//         if (connect(curr_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
//             fprintf(stderr, "client: ERROR: connecting to %s:%d\n", server_ip, server_port);
//             cleanup();
//             return EXIT_FAILURE;
//         }
//         fprintf(stdout, "client: Success!\n");
//         fprintf(stdout, "client: Sending: \"%s\"...\n", file_name);

//         int curr_file_fd = open(file_name, O_RDONLY);
//         if (curr_file_fd < 0) {
//             fprintf(stderr, "client: ERROR: Failed to open: \"%s\"\n", file_name);
//             close(curr_sock_fd);
//             curr_sock_fd = -1;
//             continue; // Skip to next file
//         }

//         while ((bytes_read = read(curr_file_fd, buffer, BUFFER_SIZE)) > 0) {
//             total_bytes_sent = 0;
//             while (total_bytes_sent < bytes_read ) {
//                 bytes_sent = send(curr_sock_fd, buffer + total_bytes_sent, bytes_read - total_bytes_sent, 0);
//                 if (bytes_sent < 0) {
//                     perror("client: ERROR: Failed to send data.");
//                     break;
//                 }
//                 total_bytes_sent += bytes_sent;
//             }
//         }

//         if (bytes_read < 0) {
//             perror("client: ERROR: Failed to read file.");
//         }

//         fprintf(stdout, "client: Done.\n");
//         close(curr_file_fd);
//         close(curr_sock_fd);
//         curr_sock_fd = -1;
//     }

//     fprintf(stdout, "client: File transfer(s) complete.\n");
//     cleanup();
//     fprintf(stdout, "client: Goodbye!\n");
//     return EXIT_SUCCESS;
// }

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE (10 * 1024 * 1024) /* 10 MB buffer size */

/* Global Variables */
char *buffer = NULL; /* Buffer to hold data */
int curr_sock_fd = -1; /* Current Socket file descriptor */

/* Function Prototypes */
void cleanup(void);
void signal_handler(int sig);

void cleanup(void) {
    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
    if (curr_sock_fd >= 0) {
        close(curr_sock_fd);
        curr_sock_fd = -1;
    }
}

void signal_handler(int sig) {
    fprintf(stderr, "\nclient: Client interrupted. Shutting down.\n");
    cleanup();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char *server_ip = NULL;
    char *endptr = NULL;
    int server_port;
    int i = 0;
    ssize_t bytes_read, bytes_sent;
    struct sockaddr_in server_addr;

    if (argc < 4) {
        fprintf(stderr, "client: USAGE: client <server_IP> <server_Port> file1 file2 ...\n");
        return EXIT_FAILURE;
    }

    server_ip = argv[1];
    server_port = strtol(argv[2], &endptr, 10);

    if (*endptr != '\0' || server_port < 0 || server_port > 65535) {
        fprintf(stderr, "client: ERROR: Invalid port number.\n");
        return EXIT_FAILURE;
    }

    signal(SIGINT, signal_handler);

    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("client: ERROR: Failed to allocate memory.");
        return EXIT_FAILURE;
    }

    for (i = 3; i < argc; i++) {
        const char *file_name = argv[i];
        ssize_t total_bytes_sent = 0;

        fprintf(stdout, "client: Connecting to %s:%d...\n", server_ip, server_port);

        curr_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (curr_sock_fd < 0) {
            perror("client: ERROR: Failed to create socket.");
            cleanup();
            return EXIT_FAILURE;
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons((unsigned short)server_port);

        if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
            perror("client: ERROR: Invalid server IP address.");
            cleanup();
            return EXIT_FAILURE;
        }

        if (connect(curr_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
            fprintf(stderr, "client: ERROR: connecting to %s:%d\n", server_ip, server_port);
            cleanup();
            return EXIT_FAILURE;
        }
        fprintf(stdout, "client: Success!\n");
        fprintf(stdout, "client: Sending: \"%s\"...\n", file_name);

        int curr_file_fd = open(file_name, O_RDONLY);
        if (curr_file_fd < 0) {
            fprintf(stderr, "client: ERROR: Failed to open: \"%s\"\n", file_name);
            close(curr_sock_fd);
            curr_sock_fd = -1;
            continue; // Skip to next file
        }

        while ((bytes_read = read(curr_file_fd, buffer, BUFFER_SIZE)) > 0) {
            ssize_t total_bytes_sent = 0;
            while (total_bytes_sent < bytes_read) {
                bytes_sent = send(curr_sock_fd, buffer + total_bytes_sent, bytes_read - total_bytes_sent, 0);
                if (bytes_sent < 0) {
                    perror("client: ERROR: Failed to send data.");
                    break;
                }
                total_bytes_sent += bytes_sent;
            }
        }

        if (bytes_read < 0) {
            perror("client: ERROR: Failed to read file.");
        }

        fprintf(stdout, "client: Done.\n");
        close(curr_file_fd);
        close(curr_sock_fd);
        curr_sock_fd = -1;
    }

    fprintf(stdout, "client: File transfer(s) complete.\n");
    cleanup();
    fprintf(stdout, "client: Goodbye!\n");
    return EXIT_SUCCESS;
}