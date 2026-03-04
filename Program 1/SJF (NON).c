#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], ct[20], wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(bt[i] > bt[j]) {
                int temp;

                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
            }
        }
    }

    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    tat[0] = bt[0];


    for(i = 1; i < n; i++) {
        ct[i] = ct[i-1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
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
