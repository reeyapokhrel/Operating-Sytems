#include <stdio.h>

void firstFit(int blocks[], int b_count, int processes[], int p_count) {
    int allocation[p_count], occupied[b_count];
    for (int i = 0; i < p_count; i++) allocation[i] = -1;
    for (int i = 0; i < b_count; i++) occupied[i] = 0;

    for (int i = 0; i < p_count; i++) {
        for (int j = 0; j < b_count; j++) {
            if (!occupied[j] && blocks[j] >= processes[i]) {
                allocation[i] = j;
                occupied[j] = 1;
                break;
            }
        }
    }

    printf("\n--- First Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < p_count; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) printf("%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}

void bestFit(int blocks[], int b_count, int processes[], int p_count) {
    int allocation[p_count], occupied[b_count];
    for (int i = 0; i < p_count; i++) allocation[i] = -1;
    for (int i = 0; i < b_count; i++) occupied[i] = 0;

    for (int i = 0; i < p_count; i++) {
        int bestIdx = -1;
        for (int j = 0; j < b_count; j++) {
            if (!occupied[j] && blocks[j] >= processes[i]) {
                if (bestIdx == -1 || blocks[bestIdx] > blocks[j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            occupied[bestIdx] = 1;
        }
    }

    printf("\n--- Best Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < p_count; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) printf("%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}

void worstFit(int blocks[], int b_count, int processes[], int p_count) {
    int allocation[p_count], occupied[b_count];
    for (int i = 0; i < p_count; i++) allocation[i] = -1;
    for (int i = 0; i < b_count; i++) occupied[i] = 0;

    for (int i = 0; i < p_count; i++) {
        int worstIdx = -1;
        for (int j = 0; j < b_count; j++) {
            if (!occupied[j] && blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[worstIdx] < blocks[j])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            occupied[worstIdx] = 1;
        }
    }

    printf("\n--- Worst Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < p_count; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) printf("%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}

int main() {
    int b_count, p_count;
    printf("Enter number of memory blocks: ");
    scanf("%d", &b_count);
    int blocks[b_count], tempBlocks[b_count];
    printf("Enter sizes of %d memory blocks: ", b_count);
    for (int i = 0; i < b_count; i++) scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &p_count);
    int processes[p_count];
    printf("Enter sizes of %d processes: ", p_count);
    for (int i = 0; i < p_count; i++) scanf("%d", &processes[i]);

    firstFit(blocks, b_count, processes, p_count);
    bestFit(blocks, b_count, processes, p_count);
    worstFit(blocks, b_count, processes, p_count);

    return 0;
}
