#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 1024

int startup_server(unsigned short port, struct sockaddr_in *p_server_addr);  //封装socket, bind, listen
int startup_client(int server_fd, struct sockaddr_in *p_client_addr);    //封装accept, 并打印客户端信息
void sys_err(const char *str);
void show_client_info(struct sockaddr_in *p_client_addr);
void *call_back(void *pclient_fd);    //pthread_create回调