#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { int v,x; }Mou;
Mou cows[20000];
struct { int c; long long s; } tree[65536];
int mycmp(const void* a, const void* b) {
    return ((const Mou*)a)->v - ((const Mou*)b)->v;
}
int main() {
    int n, i, mx = 0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &cows[i].v, &cows[i].x);
        if (mx<cows[i].x)mx = cows[i].x;
    }
    qsort(cows, n, sizeof(cows[0]), mycmp);
    int m = 1, d, k;
    while(m<=mx) m*=2;
    memset(tree, 0, 2*m*sizeof(tree[0])+4);
    long long r, ox, x, cc;
    r = 0;
    for (i=0; i<n; i++) {
        ox = cows[i].x;
        cc = 0;
        // count
        d = m; k = 0; x=ox;
        while(1) {
            if (tree[k].c==0) break;
            if (d==1) break;
            d /= 2;
            if (x<d) {
                cc += (tree[k*2+2].s - ox*tree[k*2+2].c);
                k = k*2+1;
            } else {
                cc += (ox*tree[k*2+1].c - tree[k*2+1].s);
                k = k*2+2;
                x -= d;
            }
        }
        r += cc*cows[i].v;
        // insert
        d = m; k = 0; x=ox;
        while(1) {
            tree[k].c++;
            tree[k].s += ox;
            if (d==1) break;
            d /= 2;
            if (x<d) k = k*2+1;
            else {
                k = k*2+2;
                x -= d;
            }
        }
    }
    printf("%lld\n", r);
    return 0;
}
