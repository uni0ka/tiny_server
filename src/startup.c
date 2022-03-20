#include"tiny_server.h"

int startup_server(unsigned short port){
    int server_fd = -1;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) sys_err("socket failed.");

    bind(server_fd, 
        (struct sockaddr *)&server_addr, 
        sizeof(server_addr));
    listen(server_fd, 100);

    return server_fd;
}

int startup_client(int server_fd){
   int client_fd = -1;
   
   struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_fd = accept(server_fd, 
                        (struct sockaddr *)&client_addr, 
                        &client_addr_len);
    if(client_fd < 0) sys_err("accept failed.");
    return client_fd;
}