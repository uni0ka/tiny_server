#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_CONNECTIONS 10000

void* call_back(void* arg);
void* call_back(void* arg){
    unsigned short port = *(unsigned short*)arg;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(port);
    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    sleep(3);
    char* str = "test\n";
    write(sock_fd, str, 5);
    char* buf[5];
    int read_ret = read(sock_fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, read_ret);
    
    close(sock_fd);
    return NULL;
}

int main(int argc, char** argv)
{	
    if(argc < 3){
        printf("Usage: ./client <port> <connections>\n");
        exit(1);
    }
    int connections = atoi(argv[2]);
    if(connections > MAX_CONNECTIONS){
        printf("Maximum number of connections is %d\n", MAX_CONNECTIONS);
        exit(1);
    }
    
    unsigned short port = atoi(argv[1]);

    pthread_t tid;
    int i = 0;
    while(i < connections){
        pthread_create(&tid, NULL, call_back, (void*)&port);
        pthread_detach(pthread_self());
        ++i;
    }
    
    sleep(5);
    
    return 0;
}

