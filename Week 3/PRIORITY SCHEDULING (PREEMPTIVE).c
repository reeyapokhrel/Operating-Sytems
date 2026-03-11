#include <stdio.h>

struct Process {
    int id, at, bt, priority, rt, ct, tat, wt;
};

int main() {
    int n, completed = 0, current_time = 0, min_priority = 10001;
    int shortest = 0, check = 0;
    float total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival, Burst, and Priority for P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt; // Initialize remaining time
    }

    // Loop until all processes are completed
    while (completed != n) {

        // Find the process with the highest priority available at current_time
        for (int j = 0; j < n; j++) {
            if ((p[j].at <= current_time) && (p[j].priority < min_priority) && p[j].rt > 0) {
                min_priority = p[j].priority;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            current_time++;
            continue;
        }

        // Process one unit of time
        p[shortest].rt--;

        // Update minimum priority for next iteration
        min_priority = p[shortest].rt > 0 ? p[shortest].priority : 10001;

        if (p[shortest].rt == 0) {
            completed++;
            check = 0;
            min_priority = 10001;

            p[shortest].ct = current_time + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            total_tat += p[shortest].tat;
            total_wt += p[shortest].wt;
        }
        current_time++;
    }

    printf("\nID\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
