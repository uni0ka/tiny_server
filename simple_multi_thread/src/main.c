#include"tiny_server.h"

int main(int argc, char **argv){
    if(argc < 2){
    printf("use as: ./main <port>\n");
    exit(1);
    }

    unsigned short port = atoi(argv[1]);
    struct sockaddr_in server_addr;
    int server_fd = startup_server(port, &server_addr);  

    struct sockaddr_in client_addr;
    int client_fd = -1;

    pthread_t tid;
    while(1){
        client_fd = startup_client(server_fd, &client_addr);
        int thread_created = pthread_create(&tid, 
                                            NULL,
                                            call_back,
                                            (void *)&client_fd);
        if(thread_created != 0) sys_err("pthread_create");
        pthread_detach(tid);    
    }
    return 0;
}