#include<stdio.h>
#include<stdlib.h>

int mycmp(const void *a, const void *b) {
    return *((const int*)b) -  *((const int *)a);
}
int hs[20000];
int main() {
    int n, b, i;
    scanf("%d %d", &n, &b);
    for (i=0; i<n; i++) scanf("%d", &hs[i]);
    qsort(hs, n, sizeof(hs[0]), mycmp);
    int s=0;
    for (i=0; i<n; i++) {
        s += hs[i];
        if (s>=b) break;
    }
    printf("%d\n", i+1);
    return 0;
}
