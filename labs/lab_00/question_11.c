#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAX_NUMS 10
#define MAX_RESULTS 5000

ll memo[MAX_NUMS][MAX_NUMS][MAX_RESULTS];
int memoSize[MAX_NUMS][MAX_NUMS];
int seen[MAX_NUMS][MAX_NUMS];

int nums[MAX_NUMS];
char ops[MAX_NUMS];

ll applyOp(ll a, ll b, char op) {
    if (op == '+') {
        return a + b;
    }
    if (op == '-') {
        return a - b;
    }
    return a * b;
}

void solve(int l, int r) {
    if (seen[l][r]) {
        return;
    }

    seen[l][r] = 1;
    memoSize[l][r] = 0;

    if (l == r) {
        memo[l][r][memoSize[l][r]++] = nums[l];
        return;
    }

    for (int k = l; k < r; k++) {
        solve(l, k);
        solve(k + 1, r);
        char op = ops[k];

        for (int i = 0; i < memoSize[l][k]; i++) {
            for (int j = 0; j < memoSize[k + 1][r]; j++) {
                ll leftVal = memo[l][k][i];
                ll rightVal = memo[k + 1][r][j];
                memo[l][r][memoSize[l][r]++] = applyOp(leftVal, rightVal, op);
            }
        }
    }
}

void sort(ll arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                ll temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char expression[n + 1];
    scanf("%s", expression);

    int num_count = 0;
    int op_count = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            nums[num_count++] = expression[i] - '0';
        } else {
            ops[op_count++] = expression[i];
        }
    }

    solve(0, num_count - 1);

    sort(memo[0][num_count - 1], memoSize[0][num_count - 1]);

    for (int i = 0; i < memoSize[0][num_count - 1]; i++) {
        printf("%lld ", memo[0][num_count - 1][i]);
    }
    printf("\n");

    return 0;
}
