#include <stdio.h>
#include <stdlib.h>

#define BASE 29
#define MOD 1000000007LL

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char T[n + 1], P[m + 1];
    scanf("%s %s", T, P);

    long long pow_base[n + m + 1];
    pow_base[0] = 1;
    for (int i = 1; i <= n + m; i++) {
        pow_base[i] = (pow_base[i - 1] * BASE) % MOD;
    }

    long long Hp = 0;
    for (int i = 0; i < m; i++) {
        Hp = (Hp + (long long)(P[i] - 'a' + 1) * pow_base[i]) % MOD;
    }

    long long A = 0;
    for (int i = 0; i < m; i++) {
        A = (A + (long long)(T[i] - 'a' + 1) * pow_base[i]) % MOD;
    }

    int first = 1;
    for (int k = 0; k <= n - m; k++) {
        long long lhs = (Hp * pow_base[k]) % MOD;
        if (lhs == A) {
            printf("%d ", k);
            first = 0;
        }

        if (k + m < n) {
            A = (A - (long long)(T[k] - 'a' + 1) * pow_base[k] % MOD + MOD) % MOD;
            A = (A + (long long)(T[k + m] - 'a' + 1) * pow_base[k + m]) % MOD;
        }
    }
    printf("\n");

    return 0;
}
