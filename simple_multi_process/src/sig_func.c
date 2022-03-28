#include "tiny_server.h"

void sig_wait_child()
{
    while( waitpid(0, NULL, WNOHANG) ); 
}