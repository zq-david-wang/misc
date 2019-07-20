#include<stdio.h>
#include<stdlib.h>

typedef struct {
    long long x1, y1, x2, y2, dx, dy;
    long long uy;
}Seg;

Seg segs[100000];
Seg *ps[100000], *zps[100000];

long long countx(Seg **p, int n) {
    // assuming that 0->n-1 share same p and y
    long long c = 0;
    int i, l, h, m, x; for (i=0; i<n-1; i++) {
        l = i+1; h=n;
        x = p[i]->x2;
        while(l<h) {
            m = (l+h)/2;
            if (p[m]->x1 >= x) { h = m; }
            else l = m+1;
        }
        c += (h-i-1);
    }
    return c;
}

long long county(Seg **p, int n) {
    // assuming that 0->n-1 share same p and y
    long long c = 0;
    int i, l, h, m, y; for (i=0; i<n-1; i++) {
        l = i+1; h=n;
        y = p[i]->y2;
        while(l<h) {
            m = (l+h)/2;
            if (p[m]->y1 >= y) { h = m; }
            else l = m+1;
        }
        c += (h-i-1);
    }
    return c;
}
int mycmp1(const void *a, const void*b) {
    const Seg *pa = *((const Seg**)a);
    const Seg *pb = *((const Seg**)b);
    long long v1, v2;
    v1 = pa->dy*pb->dx;
    v2 = pa->dx*pb->dy;
    if (v1 != v2) { 
        if (v1>v2) return 1;
        return -1;
    }
    v1 = pa->uy*pb->dx;
    v2 = pa->dx*pb->uy;
    if (v1 != v2) {
        if (v1>v2) return 1;
        return -1;
    }
    return pa->x1-pb->x1;
}

int mycmp2(const void *a, const void*b) {
    const Seg *pa = *((const Seg**)a);
    const Seg *pb = *((const Seg**)b);
    if (pa->x1 != pb->x1) return pa->x1-pb->x1;
    return pa->y1-pb->y1;
}

int main() {
    int c, i, n, j, k;
    int t, zc, pc;
    long long ac, x1, y1, x2, y2;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        scanf("%d", &n);
        zc = 0; pc = 0;
        for (j=0; j<n; j++) {
            scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
            if (x1>x2 || (x1==x2&&y1>y2)) {
                t=x1;x1=x2;x2=t;
                t=y1;y1=y2;y2=t;
            }
            segs[j].x1 = x1; segs[j].y1 = y1;
            segs[j].x2 = x2; segs[j].y2 = y2;
            if (x1==x2) {
                zps[zc++] = &segs[j];
            } else {
                segs[j].uy = x2*y1-x1*y2; 
                segs[j].dx = x2-x1;
                segs[j].dy = y2-y1;
                ps[pc++] = &segs[j];
            }
        }
        qsort(ps, pc, sizeof(Seg*), mycmp1);
        qsort(zps, zc, sizeof(Seg*), mycmp2);
        // printf("zps:\n"); for (j=0; j<zc; j++) printf("%lld,%lld->%lld,%lld\n", zps[j]->x1, zps[j]->y1, zps[j]->x2, zps[j]->y2); printf("\n");
        // printf("ps:\n"); for (j=0; j<pc; j++) printf("%lld,%lld-> %lld,%lld, dx: %lld, dy: %lld, uy: %lld\n", ps[j]->x1, ps[j]->y1, ps[j]->x2, ps[j]->y2, ps[j]->dx, ps[j]->dy, ps[j]->uy); printf("\n");
        ac = 0;
        k = 0;
        for (j=1; j<zc; j++) {
            if (zps[j]->x1 != zps[k]->x1) {
                ac += county(zps+k, j-k);
                k = j;
            }
        }
        ac += county(zps+k, j-k);
        k = 0;
        for (j=1; j<pc; j++) {
            if (ps[j]->dy*ps[k]->dx==ps[j]->dx*ps[k]->dy && (
                ps[j]->uy*ps[k]->dx==ps[j]->dx*ps[k]->uy)) continue;
            ac += countx(ps+k, j-k);
            k = j;
        }
        ac += countx(ps+k, j-k);
        printf("Scenario #%d:\n%lld\n\n", i, ac);
    }
    return 0;
}
