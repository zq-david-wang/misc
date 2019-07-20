#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct { int s, e, m; } PNode;
PNode pass[50000];
int seg[32768];
int mmm[32768];

int mycmp1(const void *a, const void *b) {
    return ((const PNode*)a)->e - ((const PNode*)b)->e;
}

int mycmp2(const void *a, const void *b) {
    return ((const PNode*)b)->e - ((const PNode*)a)->e;
}

void addseg(int si, int s, int e, int w, int d) {
    if (s>e) return;
    if (s==0 && e==d-1) { 
        seg[si] += w;
        mmm[si] += w;
        return;
    }
    d /= 2;
    int te = e; if (te>=d) te = d-1;
    if (s<=te) addseg(si*2+1, s, te, w, d);
    int ts = s; if (ts<d) ts = d;
    if (ts<=e) addseg(si*2+2, ts-d, e-d, w, d);
    // update mmm
    te = mmm[si*2+1];
    if (te<mmm[si*2+2]) te = mmm[si*2+2];
    mmm[si] = te+seg[si];
}
int current(int si, int s, int e, int d) {
    if (s>e) return 0;
    int m = 0;
    if (s==0 && e==d-1) {
        return mmm[si];
    }
    d /= 2;
    int te = e; if (te>=d) te = d-1;
    if (s<=te) m = seg[si] + current(si*2+1, s, te, d);
    int ts = s; if (ts<d) ts = d;
    if (ts<=e) {
        int tm = seg[si] + current(si*2+2, ts-d, e-d, d);
        if (tm>m) m = tm;
    }
    return m;
}

int main() {
    int k, n, c, i, d, rc, tc;
    scanf("%d %d %d", &k, &n, &c);
    for (i=0; i<k; i++) {
        scanf("%d %d %d", &pass[i].s, &pass[i].e, &pass[i].m);
    }
    d = 1; while(d<=n) d*=2;
    rc = 0;
    memset(seg, 0, d*2*sizeof(seg[0]));
    memset(mmm, 0, d*2*sizeof(mmm[0]));
    qsort(pass, k, sizeof(pass[0]), mycmp1);
    for (i=0; i<k; i++) {
        if (pass[i].s > pass[i].e) continue;
        tc = c - current(0, pass[i].s, pass[i].e-1, d);
        if (tc > pass[i].m) tc = pass[i].m;
        if (tc) {
            rc += tc;
            addseg(0, pass[i].s, pass[i].e-1, tc, d);
        }
    }
    memset(seg, 0, d*2*sizeof(seg[0]));
    memset(mmm, 0, d*2*sizeof(mmm[0]));
    qsort(pass, k, sizeof(pass[0]), mycmp2);
    for (i=0; i<k; i++) {
        if (pass[i].s < pass[i].e) continue;
        tc = c - current(0, pass[i].e+1, pass[i].s, d);
        if (tc > pass[i].m) tc = pass[i].m;
        if (tc) {
            rc += tc;
            addseg(0, pass[i].e+1, pass[i].s, tc, d);
        }
    }
    printf("%d\n", rc);
    return 0;
}
