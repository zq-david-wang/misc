#include<stdio.h>
#include<stdlib.h>

int mycmp(const void*a, const void*b) {
    return *((const int*)b) - *((const int*)a);
}

int offers[1000];

int main() {
    int c, i, n, j, s, b;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        printf("Scenario #%d:\n", i);
        scanf("%d %d", &b, &n);
        for (j=0; j<n; j++) scanf("%d", &offers[j]);
        qsort(offers, n, sizeof(int), mycmp);
        s = 0;
        for (j=0; j<n; j++) {
            if (s>=b) break;
            s += offers[j];
        }
        if (s>=b) printf("%d\n", j);
        else printf("impossible\n");
        printf("\n");
    }
}
