#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define MAX_CONNECTIONS 1000

void sig_wait_child(){
    while(waitpid(0, NULL, WNOHANG));
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
    
    char* port = argv[1];

    int i = 0;
    int pid = 0;
    while (i < connections){
        pid = fork();
        if(pid == -1){
            perror("fork error");
            exit(1);
        }
        else if(pid == 0)break;
        else{
            struct sigaction newact;
            newact.sa_handler = sig_wait_child;
            sigemptyset(&newact.sa_mask);
            newact.sa_flags = 0;
            sigaction(SIGCHLD, &newact, NULL);
        }
        ++i;
    }

    if(pid == 0){
    	char *argv[] = {"nc", "127.1", port, NULL};
    	execv("/bin/nc", argv);
        perror("execv error");
        exit(1);
    }  

    
    return 0;
}

