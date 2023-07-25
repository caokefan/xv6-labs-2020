#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int p[2];
    pipe(p);
    char buf[512];
    memset(buf, 0, 512);

    if(fork() == 0) {
        read(p[0], buf, 512);
        printf("%d: received %s\n", getpid(), buf);
        write(p[1], "pong", 4);
        close(p[0]);
        close(p[1]);
        exit(0);
    } else {
        write(p[1], "ping", 4);
        close(p[1]);
        wait(0);
        read(p[0], buf, 512);
        printf("%d: received %s\n", getpid(), buf);
        close(p[0]);
    }
    exit(0);
}