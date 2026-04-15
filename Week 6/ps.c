#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int burst;
    int remaining;
    int weight;
};

int main() {
    int n, time = 0, completed = 0;
    struct Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int total_weight = 0;

    // Input tasks
    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Enter Burst Time: ");
        scanf("%d", &tasks[i].burst);

        printf("Enter Weight (priority share): ");
        scanf("%d", &tasks[i].weight);

        tasks[i].remaining = tasks[i].burst;
        total_weight += tasks[i].weight;
    }

    printf("\nTotal Weight = %d\n", total_weight);

    printf("\nProportional Scheduling Execution:\n");

    // Run until all tasks complete
    while (completed < n) {
        int executed_in_cycle = 0;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {

                // Calculate time slice proportional to weight
                int slice = (tasks[i].weight * 1.0 / total_weight) * 10;

                if (slice <= 0)
                    slice = 1; // minimum 1 unit

                // Execute task
                for (int t = 0; t < slice && tasks[i].remaining > 0; t++) {
                    printf("Time %d -> Task %d\n", time, tasks[i].id);
                    tasks[i].remaining--;
                    time++;
                    executed_in_cycle = 1;

                    if (tasks[i].remaining == 0) {
                        completed++;
                        printf("Task %d completed.\n", tasks[i].id);
                    }
                }
            }
        }

        // If nothing executed (safety)
        if (!executed_in_cycle)
            break;
    }

    return 0;
}
