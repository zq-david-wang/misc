#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int w, s;
    long long u;
}Cow;
Cow cows[50000];

int mycmp(const void *a, const void *b) {
    const Cow* pa = (const Cow*)a;
    const Cow* pb = (const Cow*)b;
    if (pa->u>pb->u) return 1;
    if (pa->u<pb->u) return -1;
    return 0;
}
int main() {
    int i, n;
    long long s = 0, ts, rs;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &cows[i].w, &cows[i].s);
        s += cows[i].w;
    }
    for (i=0; i<n; i++) {
        cows[i].u = s-cows[i].w-cows[i].s;
    }
    qsort(cows, n, sizeof(cows[0]), mycmp);
    s = cows[0].w; rs = cows[0].u;
    for (i=1; i<n; i++) {
        ts = cows[i].u-s;
        if (ts > rs) rs = ts;
        s += cows[i].w;
    }
    printf("%lld\n", rs);
    return 0;
}
