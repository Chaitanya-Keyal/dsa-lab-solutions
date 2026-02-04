#include <stdio.h>
#include <stdlib.h>

struct Student {
    int marks;
    int delay;
};

int compare(struct Student* studentA, struct Student* studentB) {
    if (studentA->marks != studentB->marks) {
        return studentB->marks - studentA->marks;  // Descending order of marks
    } else {
        return studentA->delay - studentB->delay;  // Ascending order of delay
    }
}

void sort(struct Student* students, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(&students[j], &students[j + 1]) > 0) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    struct Student students[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &students[i].marks, &students[i].delay);
    }

    sort(students, n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", students[i].marks, students[i].delay);
    }

    return 0;
}
