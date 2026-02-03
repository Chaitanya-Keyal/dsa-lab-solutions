#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max = 0, total = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        total += arr[i];
    }

    int l = max, r = total;
    while (l < r) {
        int mid = (l + r) / 2;
        int painters = 1;
        int current_load = 0;
        for (int i = 0; i < n; i++) {
            if (current_load + arr[i] <= mid) {
                current_load += arr[i];
            } else {
                painters++;
                current_load = arr[i];
            }
        }
        if (painters <= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);

    return 0;
}

// clang-format off
/* Question:
The Minimum Timeline for Painting
Problem Description:
Imagine you are a manager in charge of painting a long row of boards. Each board has a
different length, and they are all lined up in a specific order that cannot be changed. You have a
team of painters and a few rules to follow. Each painter can only work on a continuous section
of boards—this means a painter cannot skip a board in the middle of their assigned section.
Every painter works at the same speed, taking exactly 1 minute to paint 1 unit of board length.
You cannot split a single board between two different painters; one person must finish the entire
board they start. Since all painters start working at the same time, the total time it takes to finish
the whole project is determined by the "busiest" painter. Your goal is to figure out a way to
assign the boards so that this maximum workload is as small as possible, effectively finding the
minimum time needed to complete the job.
Input Format
Line 1: Two integers N (the number of boards) and K (the number of painters)(K<=N).
Line 2: N space-separated integers representing the lengths of the boards in the order they are
lined up.(Length of any board>=1)
Output Format
A single integer representing the minimum possible time to finish the project.
Sample Test Case 1:
Input:
4 2
10 20 30 40
Output:
60
Explanation: Painter 1 handles [10, 20, 30] (Total: 60) and Painter 2 handles [40] (Total: 40);
the maximum time taken is 60.
Sample Test Case 2:
Input:
6 3
40 10 30 10 20 30
Output:
50
Explanation: The boards are split as [40, 10], [30, 10], and [20, 30]. The workloads are 50, 40,
and 50. The minimum possible maximum time is 50.
Note: Use of any built-in function like qsort(), bsearch(), sqrt(), etc. is not allowed
*/
