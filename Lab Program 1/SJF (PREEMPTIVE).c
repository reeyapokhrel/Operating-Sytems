#include <stdio.h>
#include <limits.h>

int main() {
    int n, bt[20], rt[20], wt[20], tat[20], at[20], ct[20], pid[20];
    int i, time = 0, count = 0, min, pos;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];  // Remaining Time
    }

    // SRTF Scheduling
    while (count < n) {
        min = INT_MAX;
        pos = -1;

        // Find process with shortest remaining time at current time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (rt[i] < min) {
                    min = rt[i];
                    pos = i;
                }
                // Tie-breaking: earlier arrival time
                else if (rt[i] == min) {
                    if (at[i] < at[pos]) {
                        pos = i;
                    }
                }
            }
        }

        if (pos == -1) {
            time++;  // CPU Idle
        }
        else {
            rt[pos]--;   // Execute 1 unit
            time++;

            if (rt[pos] == 0) {
                count++;
                ct[pos] = time;
                tat[pos] = ct[pos] - at[pos];
                wt[pos] = tat[pos] - bt[pos];
            }
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
