#include<stdio.h>
#include<stdlib.h>

typedef struct { int s, e; }MNode;
MNode mud[10000];

int mycmp(const void* a, const void *b) {
    return ((const MNode*)a)->s - ((const MNode*)b)->s;
}
int main() {
    int n, l, i, c=0, li = -1, tc;
    scanf("%d %d", &n, &l);
    for (i=0; i<n; i++) scanf("%d %d", &mud[i].s, &mud[i].e);
    qsort(mud, n, sizeof(mud[0]), mycmp);
    for (i=0; i<n; i++) {
        if (li<mud[i].s) li = mud[i].s;
        tc = (mud[i].e-li+l-1)/l;
        c += tc;
        li += tc*l;
    }
    printf("%d\n", c);
    return 0;
}
