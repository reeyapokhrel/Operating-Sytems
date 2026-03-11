#include <stdio.h>
#include <limits.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20];
    int pid[20], completed[20] = {0};
    int i, time = 0, count = 0, pos;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter number of processes: ");
    scanf("%d", &n);


    for (i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }


    while (count < n) {
        int min = INT_MAX;
        pos = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (bt[i] < min) {
                    min = bt[i];
                    pos = i;
                }

                else if (bt[i] == min) {
                    if (at[i] < at[pos]) {
                        pos = i;
                    }
                }
            }
        }

        if (pos == -1) {
            time++;  // CPU idle
        }
        else {
            time += bt[pos];      // Run full burst time
            ct[pos] = time;
            tat[pos] = ct[pos] - at[pos];
            wt[pos] = tat[pos] - bt[pos];

            completed[pos] = 1;
            count++;
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
