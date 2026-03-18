#include <stdio.h>

int main() {
    int n, i, j, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(arr[i] < arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    int secondLargest = -1;
    for(i = 1; i < n; i++) {
        if(arr[i] != arr[0]) {
            secondLargest = arr[i];
            break;
        }
    }
    printf("Second largest element: %d\n", secondLargest);

    return 0;
}
