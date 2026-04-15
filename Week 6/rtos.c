#include <stdio.h>
#include <math.h>

// Structure for a task
struct Task {
    int id;
    float C; // Execution time
    float T; // Period
};

// Function to sort tasks by period (ascending)
void sortTasks(struct Task tasks[], int n) {
    struct Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    float U = 0;

    // Input tasks
    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Enter Execution Time (C%d): ", i + 1);
        scanf("%f", &tasks[i].C);

        printf("Enter Period (T%d): ", i + 1);
        scanf("%f", &tasks[i].T);

        U += (tasks[i].C / tasks[i].T);
    }

    // Step 1: CPU Utilization
    printf("\nCPU Utilization (U) = %.4f\n", U);

    // Step 2: RMS Bound
    float bound = n * (pow(2, (1.0 / n)) - 1);
    printf("RMS Bound = %.4f\n", bound);

    // Step 3: Schedulability Check
    if (U <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n");
    }

    // Step 4: Assign Priorities (sort by period)
    sortTasks(tasks, n);

    printf("\nTask Priorities (Lower period = Higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Priority %d -> Task %d (T = %.2f)\n",
               i + 1, tasks[i].id, tasks[i].T);
    }

    // Step 5: Simple simulation (one cycle)
    printf("\nScheduling Order (One Cycle Simulation):\n");
    for (int i = 0; i < n; i++) {
        printf("Executing Task %d (C = %.2f, T = %.2f)\n",
               tasks[i].id, tasks[i].C, tasks[i].T);
    }

    return 0;
}
