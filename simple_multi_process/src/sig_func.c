#include "tiny_server.h"

void sig_wait_child()
{
    int sig = -1;
    do sig = waitpid(0, NULL, WNOHANG); while (sig > 0);
}