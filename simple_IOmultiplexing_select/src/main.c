#include"tiny_server.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage:./main <port>\n");
        exit(1);
    }

    unsigned short port = atoi(argv[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int server_fd = -1;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);  if(server_fd < 0) sys_err("socket failed");
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 100);

    int max_fd = server_fd;
    fd_set read_able_fds, all_read_fds;
    FD_ZERO(&read_able_fds);
    FD_ZERO(&all_read_fds);
    FD_SET(server_fd, &all_read_fds);

    while(1){
        read_able_fds = all_read_fds;
        int isset_num = select(max_fd+1, &read_able_fds, NULL, NULL, NULL);
        if(isset_num){
            if(FD_ISSET(server_fd, &read_able_fds)){
                struct sockaddr_in client_addr;
                socklen_t client_addr_len;
                int client_fd = accept(server_fd, 
                                       (struct sockaddr *)&client_addr, 
                                       &client_addr_len);
                //int client_fd = accept(server_fd, NULL, NULL);
                if(client_fd < 0) sys_err("accept failed");
                show_client_info(&client_addr);

                max_fd = client_fd;
                FD_SET(client_fd, &all_read_fds);
            }

            for(int i=server_fd+1; i<=max_fd; ++i){
                if(FD_ISSET(i, &read_able_fds)){
                    business_unit(i);
                }
            }
        }
    }

    close(server_fd);
    return 0;

}