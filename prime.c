#include <stdio.h>
#include <pthread.h>

void* primeGenerator(void* args) {
    int start = ((int*)args)[0];
    int end = ((int*)args)[1];

    for (int num = start; num <= end; num++) {
        int isPrime = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime && num > 1) printf("%d ", num);
    }
    return NULL;
}

int main() {
    int range[2];
    printf("Enter start and end: ");
    scanf("%d %d", &range[0], &range[1]);

    pthread_t primeThread;
    pthread_create(&primeThread, NULL, primeGenerator, (void*)range);
    pthread_join(primeThread, NULL);

    return 0;
}
