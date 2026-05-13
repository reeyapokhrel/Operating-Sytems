#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    // 1. Input Initialization
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int finish[n], safeSeq[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation: ");
        for (int j = 0; j < m; j++) scanf("%d", &alloc[i][j]);
        printf("Enter Max: ");
        for (int j = 0; j < m; j++) scanf("%d", &max[i][j]);

        // Calculate Need Matrix
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
        finish[i] = 0; // Initialize finish as false
    }

    printf("Enter Available Resources: ");
    for (int j = 0; j < m; j++) scanf("%d", &avail[j]);

    // 2. Resource Request Simulation (Deadlock Avoidance)
    int pid, request[m];
    printf("\nEnter New Request Details -- \nEnter pid: ");
    scanf("%d", &pid);
    printf("Enter Request for Resources: ");
    for (int j = 0; j < m; j++) scanf("%d", &request[j]);

    // Check if request is valid
    bool possible = true;
    for (int j = 0; j < m; j++) {
        if (request[j] > need[pid][j] || request[j] > avail[j]) {
            possible = false;
            break;
        }
    }

    if (possible) {
        // Pretend to allocate
        for (int j = 0; j < m; j++) {
            avail[j] -= request[j];
            alloc[pid][j] += request[j];
            need[pid][j] -= request[j];
        }
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    // 3. Safety Algorithm / Deadlock Detection
    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];

    int count = 0;
    printf("\nOUTPUT\n");
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) break;
                }

                if (j == m) { // If all resources for Pi can be satisfied
                    for (int k = 0; k < m; k++) work[k] += alloc[i][k];

                    printf("P%d is visited(", i);
                    for(int k=0; k<m; k++) printf(" %d", work[k]);
                    printf(" )\n");

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("SYSTEM IS IN DEADLOCK / UNSAFE STATE\n");
            return 0;
        }
    }

    printf("SYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is -- (");
    for (int i = 0; i < n; i++) printf(" P%d", safeSeq[i]);
    printf(" )\n");

    // Display Final Table
    printf("\nProcess\tAllocation\tMax\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", alloc[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}
