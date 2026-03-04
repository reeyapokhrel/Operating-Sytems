#include <stdio.h>

int main() {
    int n, i;
    int at[20], bt[20], rt[20], ct[20], wt[20], tat[20];
    int time = 0, completed = 0, shortest;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        shortest = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(shortest == -1 || rt[i] < rt[shortest])
                    shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
        } else {
            rt[shortest]--;
            time++;

            if(rt[shortest] == 0) {
                completed++;
                ct[shortest] = time;
                tat[shortest] = ct[shortest] - at[shortest];
                wt[shortest] = tat[shortest] - bt[shortest];
            }
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT");
    for(i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];

        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);

    return 0;
}
