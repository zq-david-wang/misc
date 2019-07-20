#include<stdio.h>
#include<stdlib.h>

int mycmp(const void *a, const void *b) {
    int va = *((const int*)a);
    int vb = *((const int*)b);
    if (va<0) va = -va;
    if (vb<0) vb = -vb;
    return va-vb;
}
int ps[50000];
int main() {
    int t, n, i;
    scanf("%d %d", &t, &n);
    for (i=0; i<n; i++) {
        scanf("%d", &ps[i]);
    }
    qsort(ps, n, sizeof(ps[0]), mycmp);
    int p = 0, s=0, d;
    for (i=0; i<n; i++) {
        d = ps[i]-p;
        if (d<0) d = -d;
        s += d; if (s>t) break;
        p = ps[i];
    }
    printf("%d\n", i);
    return 0;
}
