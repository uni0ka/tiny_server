#include "tiny_server.h"


void show_client_info(struct sockaddr_in *p_client_addr, int client_fd){
    struct sockaddr_in client_addr = *p_client_addr;    
    char client_IP[32];
    printf("client info:\n IP:%s ,port: %d, client_fd:%d\n",
            inet_ntop(AF_INET, 
                    &client_addr.sin_addr.s_addr, client_IP, 
                    sizeof(client_IP)),
            ntohs(client_addr.sin_port),
            client_fd);
}