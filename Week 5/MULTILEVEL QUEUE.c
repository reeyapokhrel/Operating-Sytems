#include <stdio.h>

struct process {
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int type;
};

void sortByArrival(struct process p[], int n) {
    int i, j;
    struct process temp;

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n], sys[n], user[n];
    int sc = 0, uc = 0;

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        p[i].pid = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (1-System / 0-User): ");
        scanf("%d", &p[i].type);

        if(p[i].type == 1)
            sys[sc++] = p[i];
        else
            user[uc++] = p[i];
    }

    sortByArrival(sys, sc);
    sortByArrival(user, uc);

    int time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\n--- System Processes (High Priority) ---\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < sc; i++) {
        if(time < sys[i].at)
            time = sys[i].at;

        sys[i].wt = time - sys[i].at;
        sys[i].tat = sys[i].wt + sys[i].bt;

        time += sys[i].bt;

        total_wt += sys[i].wt;
        total_tat += sys[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\n",
               sys[i].pid, sys[i].at, sys[i].bt,
               sys[i].wt, sys[i].tat);
    }

    printf("\n--- User Processes (Low Priority) ---\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < uc; i++) {
        if(time < user[i].at)
            time = user[i].at;

        user[i].wt = time - user[i].at;
        user[i].tat = user[i].wt + user[i].bt;

        time += user[i].bt;

        total_wt += user[i].wt;
        total_tat += user[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\n",
               user[i].pid, user[i].at, user[i].bt,
               user[i].wt, user[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
