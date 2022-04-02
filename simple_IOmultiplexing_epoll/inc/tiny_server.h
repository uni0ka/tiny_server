#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define BUFSIZE 1024
#define EPOLL_MAX_SIZE 10000

void sys_err(const char *str);
void business_unit(int client_fd, int *stat);
void show_client_info(struct sockaddr_in *p_client_addr, int client_fd);
