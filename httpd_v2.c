/*************************************************************************
 > File Name: httpd_v2.c
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Tue 29 Mar 2016 09:47:52 PM CST
 ************************************************************************/

#include "stdio.h"
#include "http_service.h"
#include <ctype.h>
/* #include <sys/select.h> */
/* #include <sys/time.h> */
/* #include <sys/types.h> */
#include <sys/stat.h>
#include <strings.h>
#include <string.h>

typedef struct request_field req_head;
struct request_field {
    char Host[64];
    char Referer[64];
    char User_Agent[64];
    char Date[64];
    char Connection[64];

    char Accept[64];
    char Accept_Lang[8][16];
    char Accept_Enc[8][16];
};


int read_line(int sockfd, char *buf, size_t len) {
    char c;
    unsigned int i = 0;

    while (recv(sockfd, &c, 1, 0) > 0 && i < len - 1) {
        if (c == '\r') {
            char d;
            if (recv(sockfd, &d, 1, MSG_PEEK) > 0 && d == '\n')
                recv(sockfd, &d, 1, 0);
            c = '\n';
        }
        buf[i++] = c;
        if (c == '\n')
            break;
    }
    buf[i] = '\0';
    return i;
}

int main(int argc, char *argv[])
{
    /*
     * socket variables
     */
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    int servfd, clifd;
    /*
     * file descriptor set
     */
    int maxfd;
    fd_set read_set;
    FD_ZERO(&read_set); // initial setting

    /*
     * set server socket address
     * bind and listen
     */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servfd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(servfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(servfd, 5);

    /*
     * add servfd into read_set
     * set maxfd as the biggest file descriptor
     */
    FD_SET(servfd, &read_set);
    maxfd = servfd + 1;

    while (1) {
        Select(maxfd + 1, &read_set, NULL, NULL, NULL);
        for (int fd = 0; fd <= maxfd; fd++) {
            if (!FD_ISSET(fd, &read_set)) // fd is not ready now
                continue;
            if (fd == servfd) { // server socket is ready; new client connects
                // TODO
            }
            else { // client socket is ready; client tries to say something
                // TODO
            }
        }
    }
    return 0;
}


