#include <stdio.h>

#define MAX 10

//SAFETY / BANKERS / DEADLOCK PREVENTION

void calculateNeed(int need[MAX][MAX], int max[MAX][MAX], int allocation[MAX][MAX], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int processes, int resources, int available[MAX], int max[MAX][MAX], int allocation[MAX][MAX]) {
    int need[MAX][MAX], finish[MAX], safeSequence[MAX];
    int work[MAX];

    // Calculate Need Matrix
    calculateNeed(need, max, allocation, processes, resources);

    // Initialize finish array to 0 and work as available
    for (int i = 0; i < processes; i++)
        finish[i] = 0;

    for (int i = 0; i < resources; i++)
        work[i] = available[i];

    int count = 0;
    while (count < processes) {
        int found = 0;
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == resources) {
                    // Process p can be allocated
                    for (int k = 0; k < resources; k++)
                        work[k] += allocation[p][k];
                    safeSequence[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

//SAFETY / BANKERS / DEADLOCK PREVENTION PT 2
        if (!found) {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

int main() {
    int processes, resources;
    int allocation[MAX][MAX], max[MAX][MAX], available[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Input Allocation Matrix
    printf("Enter the allocation matrix (Processes x Resources):\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("Enter the maximum matrix (Processes x Resources):\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

//SAFETY / BANKERS / DEADLOCK PREVENTION PT 3

    // Input Available Resources
    printf("Enter the available resources vector:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Check if the system is in a safe state
    isSafe(processes, resources, available, max, allocation);

    return 0;
}
