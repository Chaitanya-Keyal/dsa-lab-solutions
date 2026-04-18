#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int setId;
} Point;

int min(int a, int b) { return a < b ? a : b; }

int abs(int x) { return x < 0 ? -x : x; }

int dist(Point a, Point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

void sortByX(Point arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].x > arr[j + 1].x || (arr[j].x == arr[j + 1].x && arr[j].y > arr[j + 1].y)) {
                Point temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortRangeByY(Point arr[], int left, int right) {
    int n = right - left + 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = left; j < left + n - i - 1; j++) {
            if (arr[j].y > arr[j + 1].y || (arr[j].y == arr[j + 1].y && arr[j].x > arr[j + 1].x)) {
                Point temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int solve(Point points[], int left, int right, Point temp[], Point strip[]) {
    if (right - left <= 3) {
        int best = 1000000000;
        for (int i = left; i <= right; i++) {
            for (int j = i + 1; j <= right; j++) {
                if (points[i].setId != points[j].setId) {
                    best = min(best, dist(points[i], points[j]));
                }
            }
        }
        sortRangeByY(points, left, right);
        return best;
    }

    int mid = (left + right) / 2;
    int midX = points[mid].x;

    int leftBest = solve(points, left, mid, temp, strip);
    int rightBest = solve(points, mid + 1, right, temp, strip);
    int best = min(leftBest, rightBest);

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (points[i].y <= points[j].y) {
            temp[k++] = points[i++];
        } else {
            temp[k++] = points[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = points[i++];
    }
    while (j <= right) {
        temp[k++] = points[j++];
    }

    for (i = left; i <= right; i++) {
        points[i] = temp[i];
    }

    int stripCount = 0;
    for (i = left; i <= right; i++) {
        if (abs(points[i].x - midX) < best) {
            strip[stripCount++] = points[i];
        }
    }

    for (i = 0; i < stripCount; i++) {
        for (j = i + 1; j < stripCount && strip[j].y - strip[i].y < best; j++) {
            if (strip[i].setId != strip[j].setId) {
                best = min(best, dist(strip[i], strip[j]));
            }
        }
    }

    return best;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int total = n + m;
    Point points[total];
    Point temp[total];
    Point strip[total];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        points[i].setId = 0;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &points[n + i].x, &points[n + i].y);
        points[n + i].setId = 1;
    }

    sortByX(points, total);
    printf("%d\n", solve(points, 0, total - 1, temp, strip));
    return 0;
}
