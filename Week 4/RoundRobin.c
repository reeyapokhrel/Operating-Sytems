#include <stdio.h>

#define MAX 100

struct Process {
    int pid, at, bt;
    int rt;   // remaining time
    int ct, tat, wt, response;
    int started; // flag for first execution
};

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].rt = p[i].bt;
        p[i].started = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    // Push first arriving processes
    for(int i = 0; i < n; i++) {
        if(p[i].at == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n) {

        if(front == rear) {
            time++;
            // check for newly arrived processes
            for(int i = 0; i < n; i++) {
                if(p[i].at <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        // Response time (first time execution)
        if(p[i].started == 0) {
            p[i].response = time - p[i].at;
            p[i].started = 1;
        }

        if(p[i].rt > quantum) {
            time += quantum;
            p[i].rt -= quantum;
        } else {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

        // Add newly arrived processes
        for(int j = 0; j < n; j++) {
            if(p[j].at <= time && !visited[j]) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // Re-add current process if not finished
        if(p[i].rt > 0) {
            queue[rear++] = i;
        }
    }

    // Calculate TAT and WT
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].response);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].response;
    }

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);

    return 0;
}