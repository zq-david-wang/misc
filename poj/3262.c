#include<stdio.h>
#include<stdlib.h>

typedef struct {int t, c; }CNode;
int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    long long v1 = pa->t; v1*=pb->c;
    long long v2 = pb->t; v2*=pa->c;
    if (v1>v2) return 1;
    if (v1<v2) return -1;
    return 0;
}

CNode cows[100000];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d %d", &cows[i].t, &cows[i].c);
    qsort(cows, n, sizeof(cows[0]), mycmp);
    long long s = 0, ss = 0;
    for (i=1; i<n; i++) ss += cows[i].c;
    for (i=0; i<n-1; i++) {
        s += cows[i].t*2*ss;
        ss -= cows[i+1].c;
    }
    printf("%lld\n", s);
    return 0;
}
