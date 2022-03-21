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


    int fpid;
    while(1){
        client_fd = startup_client(server_fd, &client_addr);

        fpid = fork();
        if(fpid == -1) sys_err("fork error");
        else if(fpid == 0){       //child process
            close(server_fd);
            break;
        }
        else{                    //parent process
            close(client_fd);
            continue;
        }
    }

    if(fpid == 0){
        while(1){
            char buf[BUFSIZE];
            size_t read_ret = read(client_fd, buf, sizeof(buf));
            write(STDOUT_FILENO, buf, read_ret);

            for(size_t i = 0; i < read_ret; ++i){
                buf[i] = toupper(buf[i]);
            }

            write(client_fd, buf, read_ret);
        }
    }

    return 0;
}

