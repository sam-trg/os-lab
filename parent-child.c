#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    __pid_t pid = fork();

    if (pid == 0) {
        printf("Child process, PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        printf("Parent process, PID: %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}
