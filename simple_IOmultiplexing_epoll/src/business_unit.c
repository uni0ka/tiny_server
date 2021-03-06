#include"tiny_server.h"

void business_unit(int client_fd, int *stat){
    char buf[BUFSIZE];

    int read_ret = read(client_fd, buf, sizeof(buf));
    printf("read: %d\n", read_ret);
    if(read_ret == 0){
        close(client_fd);
        *stat = 0;
        return;
    }
    else if(read_ret == -1){
    	perror("read");
    }
    else{
        write(STDOUT_FILENO, buf, read_ret);
        for (int i = 0; i < read_ret; i++){
            buf[i] = toupper(buf[i]);
        }
        write(client_fd, buf, read_ret);
    }

    return;
}
