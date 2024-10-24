#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Function to perform Bubble Sort
void bubbleSort(char arr[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Swap arr[j] and arr[j + 1]
                char temp[100];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

// Function to perform Selection Sort
void selectionSort(char arr[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[minIndex]) < 0) {
                minIndex = j;
            }
        }
        // Swap arr[i] and arr[minIndex]
        char temp[100];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[minIndex]);
        strcpy(arr[minIndex], temp);
    }
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);
    char arr[n][100];

    // Input strings
    for (int i = 0; i < n; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    // Fork the first child for Bubble Sort
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) {
        // Child 1: Bubble Sort
        bubbleSort(arr, n);
        printf("Child 1 (Bubble Sort) finished.\n");
        // Print sorted array
        printf("Sorted strings (Bubble Sort):\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", arr[i]);
        }
        exit(0);
    } else {
        // Fork the second child for Selection Sort
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid2 == 0) {
            // Child 2: Selection Sort
            selectionSort(arr, n);
            printf("Child 2 (Selection Sort) finished.\n");
            // Print sorted array
            printf("Sorted strings (Selection Sort):\n");
            for (int i = 0; i < n; i++) {
                printf("%s\n", arr[i]);
            }
            exit(0);
        } else {
            // Parent waits for either child
            waitpid(pid1, NULL, 0); // Wait for first child
            waitpid(pid2, NULL, 0); // Wait for second child
            printf("Parent finished waiting for both children.\n");
        }
    }
    return 0;
}
