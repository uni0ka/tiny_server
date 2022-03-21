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
    int client_fd = startup_client(server_fd, &client_addr);


    char buf[BUFSIZE];
    size_t read_ret;
    while(1){
        read_ret = read(client_fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, read_ret);

        for(size_t i = 0; i < read_ret; ++i){
            buf[i] = toupper(buf[i]);
        }

        write(client_fd, buf, read_ret);

    }
    close(client_fd);
    close(server_fd);

    return 0;
}

