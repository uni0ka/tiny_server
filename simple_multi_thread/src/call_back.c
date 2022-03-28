#include"tiny_server.h"

void *call_back(void *pclient_fd){
    int client_fd = *(int*)pclient_fd;
    char buf[BUFSIZE];

    while (1){
        size_t read_ret = read(client_fd, buf, sizeof(buf));
        if(read_ret == 0)break;
        write(STDOUT_FILENO, buf, read_ret);

        for(int i=0; i<read_ret; i++){
            buf[i] = toupper(buf[i]);
        }

        write(client_fd, buf, read_ret);
    }
    close(client_fd);
    return NULL;
}