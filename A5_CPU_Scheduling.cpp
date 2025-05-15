#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100
#define MAX_CHART (MAX * MAX)

typedef struct {
    int pid, arrivalTime, burstTime, priority;
    int remainingTime, completionTime, waitingTime, turnaroundTime, startTime;
} Process;

typedef struct {
    int pid, start, end;
} Gantt;

// Print the Gantt chart
void printGantt(Gantt chart[], int m) {
    int i;
    if (m == 0) return;
    printf("\nGantt Chart:\n|");
    for (i = 0; i < m; i++) {
        printf(" P%d |", chart[i].pid);
    }
    printf("\n%d", chart[0].start);
    for (i = 0; i < m; i++) {
        printf("    %d", chart[i].end);
    }
    printf("\n");
}

// Display process table
void displayResults(Process processes[], int n) {
    int i;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

// FCFS Scheduling + Gantt
void fcfs(Process processes[], int n) {
    int currentTime = 0, i, j;
    Gantt chart[MAX];

    // sort by arrival time
    for (i = 0; i < n-1; i++)
      for (j = 0; j < n-i-1; j++)
        if (processes[j].arrivalTime > processes[j+1].arrivalTime) {
            Process tmp = processes[j];
            processes[j] = processes[j+1];
            processes[j+1] = tmp;
        }

    for (i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;
        processes[i].startTime = currentTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime    = processes[i].turnaroundTime - processes[i].burstTime;

        chart[i].pid   = processes[i].pid;
        chart[i].start = processes[i].startTime;
        chart[i].end   = processes[i].completionTime;

        currentTime = processes[i].completionTime;
    }

    displayResults(processes, n);
    printGantt(chart, n);
}

// SJF Non-Preemptive + Gantt
void sjf_non_preemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0, i, idx;
    bool isCompleted[MAX] = {false};
    Gantt chart[MAX];

    while (completed < n) {
        int minBurst = INT_MAX;
        idx = -1;
        for (i = 0; i < n; i++) {
            if (!isCompleted[i]
             && processes[i].arrivalTime <= currentTime
             && processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }
        if (idx == -1) { currentTime++; continue; }

        processes[idx].startTime = currentTime;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime    = processes[idx].turnaroundTime - processes[idx].burstTime;

        chart[completed].pid   = processes[idx].pid;
        chart[completed].start = processes[idx].startTime;
        chart[completed].end   = processes[idx].completionTime;

        currentTime = processes[idx].completionTime;
        isCompleted[idx] = true;
        completed++;
    }

    displayResults(processes, n);
    printGantt(chart, completed);
}

// Priority Non-Preemptive + Gantt
void priority_non_preemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0, i, idx;
    bool isCompleted[MAX] = {false};
    Gantt chart[MAX];

    while (completed < n) {
        int highestPriority = INT_MAX;
        idx = -1;
        for (i = 0; i < n; i++) {
            if (!isCompleted[i]
             && processes[i].arrivalTime <= currentTime
             && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { currentTime++; continue; }

        processes[idx].startTime = currentTime;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime    = processes[idx].turnaroundTime - processes[idx].burstTime;

        chart[completed].pid   = processes[idx].pid;
        chart[completed].start = processes[idx].startTime;
        chart[completed].end   = processes[idx].completionTime;

        currentTime = processes[idx].completionTime;
        isCompleted[idx] = true;
        completed++;
    }

    displayResults(processes, n);
    printGantt(chart, completed);
}

// SJF Preemptive (SRTF) + Gantt
void sjf_preemptive(Process processes[], int n) {
    int currentTime = 0, completed = 0, i, idx;
    bool isCompleted[MAX] = {false};
    Gantt chart[MAX_CHART];
    int chartIdx = 0;

    for (i = 0; i < n; i++)
        processes[i].remainingTime = processes[i].burstTime;

    while (completed < n) {
        int minRem = INT_MAX;
        idx = -1;
        for (i = 0; i < n; i++) {
            if (!isCompleted[i]
             && processes[i].arrivalTime <= currentTime
             && processes[i].remainingTime < minRem) {
                minRem = processes[i].remainingTime;
                idx = i;
            }
        }
        if (idx == -1) { currentTime++; continue; }

        // if starting first time
        if (processes[idx].remainingTime == processes[idx].burstTime)
            processes[idx].startTime = currentTime;

        // record slice
        chart[chartIdx].pid   = processes[idx].pid;
        chart[chartIdx].start = currentTime;

        // execute one unit
        processes[idx].remainingTime--;
        currentTime++;

        chart[chartIdx].end = currentTime;
        chartIdx++;

        // if finished
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime    = processes[idx].turnaroundTime - processes[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        }
    }

    displayResults(processes, n);
    printGantt(chart, chartIdx);
}

// Priority Preemptive + Gantt
void priority_preemptive(Process processes[], int n) {
    int currentTime = 0, completed = 0, i, idx;
    bool isCompleted[MAX] = {false};
    Gantt chart[MAX_CHART];
    int chartIdx = 0;

    for (i = 0; i < n; i++)
        processes[i].remainingTime = processes[i].burstTime;

    while (completed < n) {
        int highestPr = INT_MAX;
        idx = -1;
        for (i = 0; i < n; i++) {
            if (!isCompleted[i]
             && processes[i].arrivalTime <= currentTime
             && processes[i].priority < highestPr
             && processes[i].remainingTime > 0) {
                highestPr = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { currentTime++; continue; }

        if (processes[idx].remainingTime == processes[idx].burstTime)
            processes[idx].startTime = currentTime;

        chart[chartIdx].pid   = processes[idx].pid;
        chart[chartIdx].start = currentTime;

        processes[idx].remainingTime--;
        currentTime++;

        chart[chartIdx].end = currentTime;
        chartIdx++;

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime    = processes[idx].turnaroundTime - processes[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        }
    }

    displayResults(processes, n);
    printGantt(chart, chartIdx);
}

// Round Robin + Gantt
void round_robin(Process processes[], int n, int timeQuantum) {
    int remainingTime[MAX], currentTime = 0, completed = 0, i;
    bool done;
    Gantt chart[MAX_CHART];
    int chartIdx = 0;

    for (i = 0; i < n; i++)
        remainingTime[i] = processes[i].burstTime;

    while (completed < n) {
        done = false;
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && processes[i].arrivalTime <= currentTime) {
                done = true;
                int sliceStart = currentTime;

                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime  = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime     = processes[i].turnaroundTime - processes[i].burstTime;
                    remainingTime[i] = 0;
                    completed++;
                }

                chart[chartIdx].pid   = processes[i].pid;
                chart[chartIdx].start = sliceStart;
                chart[chartIdx].end   = currentTime;
                chartIdx++;
            }
        }
        if (!done) currentTime++;
    }

    displayResults(processes, n);
    printGantt(chart, chartIdx);
}

int getProcesses(Process processes[]) {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Arrival, Burst, Priority for P%d: ", i + 1);
        scanf("%d%d%d",
            &processes[i].arrivalTime,
            &processes[i].burstTime,
            &processes[i].priority);
    }
    return n;
}

int main() {
    Process processes[MAX];
    int choice, n, tq;

    while (1) {
        printf("\nCPU Scheduling Algorithms\n"
               "1. FCFS (NP)\n"
               "2. SJF (NP)\n"
               "3. Priority (NP)\n"
               "4. Round Robin\n"
               "5. SJF (Preemptive)\n"
               "6. Priority (Preemptive)\n"
               "7. Exit\n"
               "Choice: ");
        scanf("%d", &choice);
        if (choice == 7) break;

        n = getProcesses(processes);
        switch (choice) {
            case 1: fcfs(processes, n); break;
            case 2: sjf_non_preemptive(processes, n); break;
            case 3: priority_non_preemptive(processes, n); break;
            case 4:
                printf("Enter Time Quantum: ");
                scanf("%d", &tq);
                round_robin(processes, n, tq);
                break;
            case 5: sjf_preemptive(processes, n); break;
            case 6: priority_preemptive(processes, n); break;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
