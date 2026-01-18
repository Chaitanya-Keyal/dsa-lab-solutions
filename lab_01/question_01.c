#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    struct Student {
        int ID;
        char Name[50];
        float Marks[3];
        float Average;
    } students[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %s %f %f %f", &students[i].ID, students[i].Name,
              &students[i].Marks[0], &students[i].Marks[1],
              &students[i].Marks[2]);
        students[i].Average = (students[i].Marks[0] + students[i].Marks[1] +
                               students[i].Marks[2]) /
                              3.0;
    }
    printf("Merit List:\n");
    for (int i = 0; i < N; i++) {
        if (students[i].Average > 75.0) {
            printf("%d %s (Avg: %.2f)\n", students[i].ID, students[i].Name,
                   students[i].Average);
        }
    }
    struct Student topper = students[0];
    for (int i = 1; i < N; i++) {
        if (students[i].Average > topper.Average) {
            topper = students[i];
        }
    }
    printf("Topper: %s", topper.Name);

    return 0;
}
