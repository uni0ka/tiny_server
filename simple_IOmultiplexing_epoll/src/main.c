#include"tiny_server.h"

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: ./main <port>\n");
        exit(1);
    }

    unsigned short port = atoi(argv[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) sys_err("socket failed");
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 1000);
    printf("server created. server_fd = %d\n", server_fd);

    int epoll_fd = epoll_create(EPOLL_MAX_SIZE);
    if(epoll_fd < 0) sys_err("epoll_create failed");

    struct epoll_event server_event;
    struct epoll_event ready_events[EPOLL_MAX_SIZE];
    server_event.events = EPOLLIN;
    server_event.data.fd = server_fd;
    if( epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &server_event) == -1) sys_err("epoll_ctl failed");

    while (1){
        int ready_num = epoll_wait(epoll_fd, ready_events, EPOLL_MAX_SIZE, -1);

        for(int i= 0; i <= ready_num; ++i){
            if((ready_events[i].events & EPOLLIN) != 1)continue;
            if(ready_events[i].data.fd == server_fd){
                struct sockaddr_in client_addr;
                socklen_t client_addr_len;
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                //int client_fd = accept(server_fd, NULL, NULL);
                if(client_fd < 0) sys_err("accept failed");
                show_client_info(&client_addr, client_fd);

                struct epoll_event client_event;
                client_event.events = EPOLLIN;
                client_event.data.fd = client_fd;
                if( epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) sys_err("epoll_ctl failed");
            }
            else{
                int tmp_client_fd = ready_events[i].data.fd;
                int read_stat = 1;
                business_unit(tmp_client_fd, &read_stat);
                if(read_stat == 0){
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, tmp_client_fd, NULL);
                    printf("client closed, fd:%d\n", tmp_client_fd);
                }
            }
        }
    }
    
    close(server_fd);
    close(epoll_fd);
    
    return 0;
}
