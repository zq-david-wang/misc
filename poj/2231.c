#include<stdio.h>
#include<stdlib.h>

int mycmp(const void*a, const void*b) {
    return *((const int*)a) - *((const int*)b);
}

int locs[10000];
int main() {
    int n, i;
    long long s=0, r=0, d;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &locs[i]);
    qsort(locs, n, sizeof(locs[0]), mycmp);
    for (i=0; i<n-1; i++) {
        d = locs[i+1]-locs[i];
        d *= (n-1-i+r);
        s += d;
        r -= i;
        r += (n-1-i-1);
    }
    s *= 2;
    printf("%lld\n", s);
    return 0;
}

