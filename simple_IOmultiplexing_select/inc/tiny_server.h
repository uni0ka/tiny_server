#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ctype.h>

#define BUFSIZE 1024


void sys_err(const char *str) ;
void show_client_info(struct sockaddr_in *p_client_addr);
void business_unit(int client_fd);

