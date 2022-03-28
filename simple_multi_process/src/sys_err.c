#include"tiny_server.h"

void sys_err(const char *str) {
    perror(str);
    exit(1);
}