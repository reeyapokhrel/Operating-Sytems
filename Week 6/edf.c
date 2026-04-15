#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 10

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int deadline;
    int weight;
    int completed;
} Process;

// ---------------- EDF SCHEDULER ----------------
void EDF_Scheduler(Process p[], int n) {
    float U = 0.0;

    // Step 1: CPU Utilization
    for (int i = 0; i < n; i++) {
        U += (float)p[i].burst / p[i].deadline;
    }

    // Step 2: Feasibility Check
    if (U > 1.0) {
        printf("\nEDF: Scheduling not feasible (deadlines may be missed)\n");
    } else {
        printf("\nEDF: Scheduling feasible\n");
    }

    int t = 0, completed = 0;

    printf("\nExecution Order (EDF):\n");

    while (completed < n) {
        int idx = -1;
        int min_deadline = 1e9;

        // Find process with earliest deadline
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && p[i].remaining > 0) {
                if (p[i].deadline < min_deadline) {
                    min_deadline = p[i].deadline;
                    idx = i;
                }
            }
        }

        // If no process is ready
        if (idx == -1) {
            t++;
            continue;
        }

        // Execute for 1 unit
        printf("Time %d: P%d\n", t, p[idx].id);
        p[idx].remaining--;

        // If completed
        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed++;
        }

        t++;
    }
}

// ---------------- PROPORTIONAL SHARE ----------------
void Proportional_Share(Process p[], int n) {
    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        total_weight += p[i].weight;
    }

    int completed = 0;

    printf("\nExecution Order (Proportional Share):\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {

            if (p[i].remaining > 0) {
                // Calculate time slice
                int time_slice = (p[i].weight * TIME_QUANTUM) / total_weight;
                if (time_slice <= 0) time_slice = 1;

                printf("P%d runs for %d units\n", p[i].id, time_slice);

                p[i].remaining -= time_slice;

                if (p[i].remaining <= 0) {
                    p[i].remaining = 0;
                    p[i].completed = 1;
                    completed++;
                    total_weight -= p[i].weight;
                }
            }
        }
    }
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int n;
    Process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].id = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline: ");
        scanf("%d", &p[i].deadline);

        printf("Weight: ");
        scanf("%d", &p[i].weight);

        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    // Copy for second algorithm
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }

    // Run EDF
    EDF_Scheduler(p, n);

    // Reset remaining times for proportional share
    for (int i = 0; i < n; i++) {
        temp[i].remaining = temp[i].burst;
        temp[i].completed = 0;
    }

    // Run Proportional Share
    Proportional_Share(temp, n);

    return 0;
}
