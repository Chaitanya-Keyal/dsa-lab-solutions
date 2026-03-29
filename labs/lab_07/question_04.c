#include <stdio.h>
#include <stdlib.h>

#define MAX 1000005

int q[MAX];
int f = 0, r = -1, cnt = 0;

void enqueue(int x) {
    q[++r] = x;
    cnt++;
}

int dequeue() {
    cnt--;
    return q[f++];
}

int front() { return q[f]; }

int size() { return cnt; }

int main() {
    int m, n;
    int grid[12][12], dist[12][12];
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
            dist[i][j] = -1;
        }
    }

    enqueue(0);
    dist[0][0] = 1;

    while (size() > 0) {
        int cur = dequeue();
        int x = cur / n;
        int y = cur % n;

        if (grid[x][y] == 2) {
            printf("%d\n", dist[x][y]);
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dr[k];
            int ny = y + dc[k];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (grid[nx][ny] == 1 || dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1;
            enqueue(nx * n + ny);
        }
    }

    return 0;
}
