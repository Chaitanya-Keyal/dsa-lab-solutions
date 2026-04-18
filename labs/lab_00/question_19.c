#include <stdio.h>
#include <stdlib.h>

#define MAX_BUILDINGS 10000
#define MAX_POINTS (2 * MAX_BUILDINGS)

typedef struct {
    int x;
    int h;
} Point;

int addPoint(Point sky[], int size, int x, int h) {
    if (size > 0 && sky[size - 1].x == x) {
        sky[size - 1].h = h;
    } else {
        sky[size].x = x;
        sky[size].h = h;
        size++;
    }

    if (size >= 2 && sky[size - 1].h == sky[size - 2].h) {
        size--;
    }

    return size;
}

int mergeSkyline(Point left[], int leftSize, Point right[], int rightSize, Point out[]) {
    int i = 0;
    int j = 0;
    int lh = 0;
    int rh = 0;
    int outSize = 0;

    while (i < leftSize && j < rightSize) {
        int x;
        if (left[i].x < right[j].x) {
            x = left[i].x;
            lh = left[i].h;
            i++;
        } else if (left[i].x > right[j].x) {
            x = right[j].x;
            rh = right[j].h;
            j++;
        } else {
            x = left[i].x;
            lh = left[i].h;
            rh = right[j].h;
            i++;
            j++;
        }
        outSize = addPoint(out, outSize, x, lh > rh ? lh : rh);
    }

    while (i < leftSize) {
        lh = left[i].h;
        outSize = addPoint(out, outSize, left[i].x, lh > rh ? lh : rh);
        i++;
    }

    while (j < rightSize) {
        rh = right[j].h;
        outSize = addPoint(out, outSize, right[j].x, lh > rh ? lh : rh);
        j++;
    }

    return outSize;
}

int solve(int buildings[][3], int left, int right, Point out[]) {
    if (left == right) {
        int outSize = 0;
        outSize = addPoint(out, outSize, buildings[left][0], buildings[left][2]);
        outSize = addPoint(out, outSize, buildings[left][1], 0);
        return outSize;
    }

    int mid = (left + right) / 2;
    Point leftSky[MAX_POINTS];
    Point rightSky[MAX_POINTS];

    int leftSize = solve(buildings, left, mid, leftSky);
    int rightSize = solve(buildings, mid + 1, right, rightSky);
    return mergeSkyline(leftSky, leftSize, rightSky, rightSize, out);
}

int main() {
    int n;
    scanf("%d", &n);
    int buildings[n][3];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &buildings[i][0], &buildings[i][1], &buildings[i][2]);
    }

    Point ans[2 * n];
    int ansSize = solve(buildings, 0, n - 1, ans);
    for (int i = 0; i < ansSize; i++) {
        printf("%d %d ", ans[i].x, ans[i].h);
    }
    printf("\n");

    return 0;
}
