#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], pid[20];
    int i, j;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }


    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap Arrival Time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap Burst Time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap Process ID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // FCFS Scheduling
    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    tat[0] = bt[0];

    for (i = 1; i < n; i++) {
        if (ct[i - 1] < at[i]) {
            ct[i] = at[i] + bt[i];  // CPU idle case
            wt[i] = 0;
        } else {
            wt[i] = ct[i - 1] - at[i];
            ct[i] = ct[i - 1] + bt[i];
        }

        tat[i] = wt[i] + bt[i];
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output Table
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");

    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
