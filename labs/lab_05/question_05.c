#include <stdio.h>
#include <stdlib.h>

int divisors(int num) {
    int count = 0;
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            count++;
            if (i != num / i) {
                count++;
            }
        }
    }
    return count;
}

int compare(int a, int b) {
    int divA = divisors(a);
    int divB = divisors(b);
    if (divA != divB) {
        return divA - divB;  // Ascending order of divisors
    } else {
        return b - a;  // Descending order of values
    }
}

int sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
