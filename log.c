/*************************************************************************
 > File Name: log.c
 > Author: Hac
 > Mail: hac@zju.edu.cn
 > Created Time: Sun 03 Apr 2016 08:33:52 PM CST
 ************************************************************************/

/*
 * Access Log:
 *
 * IP_ADDRESS - - DATE|TIME TRANCACTION USER_AGENT
 */

/*
 * Error Log:
 *
 * TYPE - - DATE|TIME TRANSACTION COMMENT
 */

/* extern int fd_access; */
int fd_access;
extern int fd_error;

#include "stdio.h"
#include <strings.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "http_service.h"

int access_log(struct sockaddr_in remote, const char *request, const char *user_agent) {
    char *ip;
    char time_str[63];
    char record[512];
    time_t rawtime;
    struct tm *timeinfo;

    bzero(record, sizeof(record));
    ip = inet_ntoa(remote.sin_addr);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_str, sizeof(time_str), "%d/%b/%G:%X %z", timeinfo);
    sprintf(record, "%s - - [%s] \"%s\" \"%s\"\n", ip, time_str, request, user_agent);

    Written(fd_access, record, strlen(record));
    return 0;
}

int main(int argc, char *argv[])
{
    fd_access = open("access.log", O_WRONLY | O_APPEND);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    access_log(servaddr, "GET / HTTP/1.1", "Ember");

    return 0;
}

/* int error_log(const char *comment) { */

/* } */
