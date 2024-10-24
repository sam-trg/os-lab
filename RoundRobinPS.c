#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;          // Process ID
    int burstTime;    // Burst time of the process
    int arrivalTime;  // Arrival time of the process
    int remainingTime; // Remaining burst time of the process
    int completionTime; // Completion time of the process
    int waitingTime;   // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

void roundRobinScheduling(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0;
    int completedProcesses = 0;
    int i = 0;

    while (completedProcesses < n) {
        if (processes[i].remainingTime > 0 )  {
            if (processes[i].remainingTime <= timeQuantum) {
                currentTime += processes[i].remainingTime;
                processes[i].remainingTime = 0;
                processes[i].completionTime = currentTime;
                processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                completedProcesses++;
            } else {
                processes[i].remainingTime -= timeQuantum;
                currentTime += timeQuantum;
            }
        }
        i = (i + 1) % n; // Move to the next process
    }
}

void printProcessTable(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n, timeQuantum;
    struct Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    roundRobinScheduling(processes, n, timeQuantum);
    printProcessTable(processes, n);

    return 0;
}
