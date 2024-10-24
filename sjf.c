#include <stdio.h>

//Shortest Job First

struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int waiting;   // Waiting Time
    int turnaround; // Turnaround Time
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0, completed = 0, minIndex;
    int totalWaiting = 0, totalTurnaround = 0;

    // Initialize waiting and turnaround times to 0
    for (int i = 0; i < n; i++) {
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    while (completed < n) {
        // Find the process with the shortest burst time among the arrived processes
        minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].burst > 0) {
                if (minIndex == -1 || p[i].burst < p[minIndex].burst) {
                    minIndex = i;
                }
            }
        }

//Shortest Job First Pt 2S

        if (minIndex != -1) {
            // Process the selected job
            currentTime += p[minIndex].burst;
            p[minIndex].turnaround = currentTime - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;

            // Print the execution details of the process
            printf("Process P%d executed from time %d to %d.\n", p[minIndex].pid, currentTime - p[minIndex].burst, currentTime);

            // Mark the process as completed by setting burst time to 0
            p[minIndex].burst = 0;
            completed++;
        } else {
            // If no process has arrived yet, increment the current time
            currentTime++;
        }
    }

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    // Display process times
    printf("\nProcess ID | Arrival Time | Waiting Time | Turnaround Time\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d         | %d            | %d            | %d\n", p[i].pid, p[i].arrival, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
}

// SHORTEST JOB FIRST PT 3
int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1; // Assign process ID
    }

    // Sort processes by their arrival time
    sortByArrival(p, n);

    // Calculate waiting time, turnaround time, and display the results
    calculateTimes(p, n);

    return 0;
}
