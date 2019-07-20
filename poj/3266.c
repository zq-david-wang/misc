#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int a, b;
}CNode;
CNode scores[50000];
int pns[50000];
int rpns[50000];
int rs[50000];

int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    return pa->a*pb->b-pb->a*pa->b;
}

int bfind(int s, int e, long long  a, long long b) {
    int m, d;
    while(s<=e) {
        m = (s+e)/2;
        d = scores[m].a*b - scores[m].b*a;
        if (d==0) return m-1;
        if (d>0) { if (e==m) break; e = m; }
        else s = m+1;
    }
    if (d<0) return m;
    return m-1;
}
int main() {
    int n, i, sa, sb, j;
    int ni, ei;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d %d", &scores[i].a, &scores[i].b);
    qsort(scores, n, sizeof(scores[0]), mycmp);
    sa = 0; sb = 0;
    for (i=1; i<n; i++) {
        sa += scores[i].a;
        sb += scores[i].b;
    }
    pns[0] = 0;
    for (i=1; i<n; i++) {
        if (scores[i-1].b >= scores[i].b) pns[i] = pns[i-1];
        else pns[i] = i;
    }
    rpns[n-1] = n-1;
    for (i=n-2; i>=0; i--) {
        if (scores[i+1].b <= scores[i].b) rpns[i] = rpns[i+1];
        else rpns[i] = i;
    }
    long long la, lb, cla, clb;
    int rc = 0;
    int nni = 1;
    for (i=1; i<n-1; i++) {
        /// ei = bfind(i, n-1, sa, sb)+1;
        ei = n-1;
        la = sa; lb = sb;
        for (j=ei; j>=i; ) {
            // ni = pns[j];
            ni = j;
            if (ni < i) ni = j;
            cla = sa-scores[ni].a;
            clb = sb-scores[ni].b;
            if (cla*lb>la*clb) {
                la = cla;
                lb = clb;
                nni = j;
            }
            j = ni-1;
        }
        for (j=i-1; j>=0; j--) {
            // ni = rpns[j];
            cla = la+scores[j].a;
            clb = lb+scores[j].b;
            if (cla*sb > sa*clb) break;
            //
        }
        if (j>=0) rs[rc++] = i;
        sa -= scores[i].a;
        sb -= scores[i].b;
    }
    printf("%d\n", rc);
    for (i=0; i<rc; i++) {
        printf("%d\n", rs[i]);
    }
    return 0;
}

