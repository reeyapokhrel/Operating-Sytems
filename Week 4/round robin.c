#include <stdio.h>

int main() {
    int n, i, time = 0, remain, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], rem_bt[n], wait[n], tat[n];

    for(i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst[i]);
        rem_bt[i] = burst[i];  // remaining burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    remain = n;

    while(remain > 0) {
        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                if(rem_bt[i] <= quantum) {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    tat[i] = time;
                    wait[i] = tat[i] - burst[i];
                    remain--;
                } else {
                    rem_bt[i] -= quantum;
                    time += quantum;
                }
            }
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst[i], wait[i], tat[i]);
        total_wt += wait[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
