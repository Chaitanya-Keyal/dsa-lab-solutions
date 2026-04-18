#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

typedef struct {
    int sum0;
    int sum1;
    int pref0;
    int pref1;
    int suff0;
    int suff1;
    int best1;
} Node;

Node merge(Node left, Node right) {
    Node out;

    out.sum0 = left.sum0 + right.sum0;
    out.sum1 = max(left.sum1 + right.sum0, left.sum0 + right.sum1);

    out.pref0 = max(left.pref0, left.sum0 + right.pref0);
    out.pref1 = max(left.pref1, max(left.sum1 + right.pref0, left.sum0 + right.pref1));

    out.suff0 = max(right.suff0, right.sum0 + left.suff0);
    out.suff1 = max(right.suff1, max(right.sum1 + left.suff0, right.sum0 + left.suff1));

    int crossL = left.suff1 + right.pref0;
    int crossR = left.suff0 + right.pref1;
    out.best1 = max(left.best1, max(right.best1, max(crossL, crossR)));

    return out;
}

Node solve(int arr[], int left, int right) {
    if (left == right) {
        Node base;
        int x = arr[left];
        int sq = x * x;

        base.sum0 = x;
        base.sum1 = sq;
        base.pref0 = x;
        base.pref1 = sq;
        base.suff0 = x;
        base.suff1 = sq;
        base.best1 = sq;
        return base;
    }

    int mid = (left + right) / 2;
    Node leftNode = solve(arr, left, mid);
    Node rightNode = solve(arr, mid + 1, right);
    return merge(leftNode, rightNode);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node ans = solve(arr, 0, n - 1);
    printf("%d\n", ans.best1);
    return 0;
}
