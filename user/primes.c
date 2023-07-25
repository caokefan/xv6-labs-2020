#include "kernel/types.h"
#include "user/user.h"

void prime(int fd)
{
    int cur;
    if(!read(fd, &cur, sizeof(cur))) return;
    printf("prime %d\n", cur);
    int p[2];
    pipe(p);

    if(fork()==0) {
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        int num;
        while(read(fd, &num, sizeof(num))) {
            if(num % cur) {
                write(p[1], &num, sizeof(num));
            }
        }
        close(p[1]);
        wait(0);
    }
}

int main(int argc, char* argv[])
{
    int p[2];
    pipe(p);

    if(fork()==0) {
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        for(int i=2;i<=35;++i) {
            if(!write(p[1], &i, sizeof(i))) {
                printf("write error\n");
            }
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}