#include <stdio.h>
#include <pthread.h>

int even_sum = 0, odd_sum = 0;

void* sumEven(void* args) {
    int* arr = (int*)args;
    for (int i = 0; i < 10; i++) {
        if (arr[i] % 2 == 0)
            even_sum += arr[i];
    }
    return NULL;
}

void* sumOdd(void* args) {
    int* arr = (int*)args;
    for (int i = 0; i < 10; i++) {
        if (arr[i] % 2 != 0)
            odd_sum += arr[i];
    }
    return NULL;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t t1, t2;

    pthread_create(&t1, NULL, sumEven, (void*)arr);
    pthread_create(&t2, NULL, sumOdd, (void*)arr);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum of even: %d\n", even_sum);
    printf("Sum of odd: %d\n", odd_sum);

    return 0;
}
