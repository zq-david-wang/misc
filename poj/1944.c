#include<stdio.h>
#include<stdlib.h>
typedef struct { int a, b; }SNode;
SNode sg[10000];

int mycmp(const void *a, const void *b) {
    return ((const SNode*)a)->a - ((const SNode *)b)->a;
}
int main() {
    int n, p, i;
    int a, b, t;
    scanf("%d %d", &n, &p);
    for (i=0; i<p; i++) {
        scanf("%d %d", &a, &b);
        if (a>b) { t=a; a=b; b=t; }
        sg[i].a = a;
        sg[i].b = b;
    }
    qsort(sg, p, sizeof(sg[0]), mycmp);
    // for (i=0; i<p; i++) printf("%d,%d ", sg[i].a, sg[i].b); printf("\n");
    int mc=n, cc, j, mxl, mnr, ls, le;
    for (i=1; i<=n; i++) {
        mxl = 0; mnr = n;
        for (j=0; j<p; j++) {
            if (sg[j].a>=i) break;
            if (sg[j].a<i && sg[j].b>=i) {
                if (mxl<sg[j].a) mxl = sg[j].a;
                if (mnr>sg[j].b) mnr = sg[j].b;
            }
        }
        // printf("%d: mxl:%d mnr: %d\n", i, mxl, mnr);
        ls = 0; le = mxl;
        cc = 0;
        for (j=0; j<p; j++) {
            if (sg[j].a>=i) break;
            if (sg[j].b>=i) continue;
            if (sg[j].a>le) {
                cc += le-ls;
                if (cc>=mc) break;
                ls = sg[j].a; le = sg[j].b;
            } else {
                if (le<sg[j].b) le = sg[j].b;
            }
        }
        cc += le-ls;
        if (cc>=mc) continue;
        ls = 0; le = 0;
        for (; j<p; j++) {
            if (sg[j].a>le) {
                cc += le-ls;
                if (cc>=mc) break;
                ls = sg[j].a; le = sg[j].b;
                if (ls>mnr) ls = mnr;
            } else {
                if (le<sg[j].b) le = sg[j].b;
            }
            if (le>=mnr) { le = n; break; }
        }
        cc += le-ls;
        if (le<=mnr) cc+= (n-mnr);
        if (cc>=mc) continue;
        if (mc > cc) mc = cc;
        // printf("pivot %d ==> %d\n", i, cc);
    }
    printf("%d\n", mc);
    return 0;
}
