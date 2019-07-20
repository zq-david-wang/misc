#include<stdio.h>
#include<stdlib.h>

typedef struct{ int a, b, i; }VNode;
VNode vs[50000];
int mycmp(const void*a, const void*b) {
    return ((const VNode*)b)->a - ((const VNode*)a)->a;
}
int main() {
    int n, k, i;
    scanf("%d %d", &n, &k);
    for (i=0; i<n; i++) {
        scanf("%d %d", &vs[i].a, &vs[i].b);
        vs[i].i = i+1;
    }
    qsort(vs, n, sizeof(vs[0]), mycmp);
    int mi, mv=0;
    for (i=0;  i<k; i++) {
        if (vs[i].b>mv) {
            mv = vs[i].b;
            mi = vs[i].i;
        }
    }
    printf("%d\n", mi);
    return 0;
}
