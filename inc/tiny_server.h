#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFSIZE 1024



int startup_server(unsigned short port, struct sockaddr_in *p_server_addr);
int startup_client(int server_fd, struct sockaddr_in *p_client_addr);
void sys_err(const char *str);
void show_client_info(struct sockaddr_in *p_client_addr);