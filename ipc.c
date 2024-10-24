#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

//parent send char to child. child increase char by 1.
int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(char), 0666 | IPC_CREAT);
    char* shared_memory = (char*)shmat(shmid, NULL, 0);

    __pid_t pid = fork();
    if (pid == 0) {
        *shared_memory += 1;
        exit(0);
    } else {
        *shared_memory = 'A';
        wait(NULL);
        printf("Received from child: %c\n", *shared_memory);
    }
    return 0;
}
