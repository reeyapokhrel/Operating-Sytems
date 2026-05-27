#include <stdio.h>

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

void fifo(int ref[], int n, int f_count) {
    int frames[f_count], pf = 0, next = 0;
    for (int i = 0; i < f_count; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f_count; j++) if (frames[j] == ref[i]) found = 1;

        if (!found) {
            frames[next] = ref[i];
            next = (next + 1) % f_count;
            pf++;
            printf("PF No. %d: ", pf);
            printFrames(frames, f_count);
        }
    }
    printf("FIFO Page Faults: %d\n", pf);
}

void lru(int ref[], int n, int f_count) {
    int frames[f_count], time[f_count], pf = 0;
    for (int i = 0; i < f_count; i++) frames[i] = -1;

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0, pos;
        for (int j = 0; j < f_count; j++) if (frames[j] == ref[i]) { found = 1; time[j] = i; }

        if (!found) {
            pf++;
            if (i < f_count && frames[i] == -1) pos = i;
            else {
                pos = 0;
                int min = time[0];
                for (int j = 1; j < f_count; j++) if (time[j] < min) { min = time[j]; pos = j; }
            }
            frames[pos] = ref[i];
            time[pos] = i;
            printf("PF No. %d: ", pf);
            printFrames(frames, f_count);
        }
    }
    printf("LRU Page Faults: %d\n", pf);
}

void optimal(int ref[], int n, int f_count) {
    int frames[f_count], pf = 0;
    for (int i = 0; i < f_count; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f_count; j++) if (frames[j] == ref[i]) found = 1;

        if (!found) {
            pf++;
            int pos = -1;
            for(int j=0; j<f_count; j++) if(frames[j] == -1) { pos = j; break; }

            if (pos == -1) {
                int farthest = i, res = -1;
                for (int j = 0; j < f_count; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == ref[k]) {
                            if (k > farthest) { farthest = k; res = j; }
                            break;
                        }
                    }
                    if (k == n) { res = j; break; }
                }
                pos = res;
            }
            frames[pos] = ref[i];
            printf("PF No. %d: ", pf);
            printFrames(frames, f_count);
        }
    }
    printf("Optimal Page Faults: %d\n", pf);
}

int main() {
    int f_count, n;
    printf("Enter the number of Frames: ");
    scanf("%d", &f_count);
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    int ref[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    fifo(ref, n, f_count);
    lru(ref, n, f_count);
    optimal(ref, n, f_count);
    return 0;
}
