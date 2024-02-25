#include <stdio.h>
void waitingTime(int processes[], int n, int burst_time[], int wt[], int quantum) {
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = burst_time[i];

    int t = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - burst_time[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done)
            break;
    }
}
void turnaroundTime(int processes[], int n, int burst_time[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = burst_time[i] + wt[i];
}
void findAvgTime(int processes[], int n, int burst_time[], int quantum) {
    int wt[n], tat[n];
    waitingTime(processes, n, burst_time, wt, quantum);
    turnaroundTime(processes, n, burst_time, wt, tat);
    printf("Processes\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wt[i], tat[i]);
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
}
int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {8, 6, 12};
    int quantum = 2;
    findAvgTime(processes, n, burst_time, quantum);
    return 0;
}
