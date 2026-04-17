#include <stdio.h>
#include <stdlib.h>

int dp[1001];

int maxEnergyLinear(int index, int end, int energy_output[]) {
    if (index > end) {
        return 0;
    }
    if (dp[index] != -1) {
        return dp[index];
    }

    int take = energy_output[index] + maxEnergyLinear(index + 2, end, energy_output);
    int skip = maxEnergyLinear(index + 1, end, energy_output);
    dp[index] = take > skip ? take : skip;
    return dp[index];
}

int maxEnergyCircular(int n, int energy_output[]) {
    if (n == 1) {
        return energy_output[0];
    }

    for (int i = 0; i < 1001; i++) {
        dp[i] = -1;
    }
    int case1 = maxEnergyLinear(0, n - 2, energy_output);

    for (int i = 0; i < 1001; i++) {
        dp[i] = -1;
    }
    int case2 = maxEnergyLinear(1, n - 1, energy_output);

    return case1 > case2 ? case1 : case2;
}

int main() {
    int n;
    scanf("%d", &n);
    int energy_output[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &energy_output[i]);
    }

    printf("%d\n", maxEnergyCircular(n, energy_output));
    return 0;
}
