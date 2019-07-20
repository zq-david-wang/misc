#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct { int s, e, p; } CNode;
CNode cow[10000];
long long  dp[10000];
int gn, ge, gs;
long long dfs(int ci) {
    if (dp[ci] != -1) return dp[ci];
    if (cow[ci].e>=ge) {
        dp[ci] = cow[ci].p;
        return cow[ci].p;
    }
    long long r = -2, t;
    int i; for (i=ci+1; i<gn; i++) {
        if (cow[i].s > cow[ci].e+1) break;
        if (cow[i].e <= cow[ci].e) continue;
        t = dfs(i);
        if (r<0 || (t>=0 && t<r))r= t;
    }
    if (r>=0) r+=cow[ci].p;
    dp[ci] = r;
    return r;
}
int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    if (pa->s!=pb->s) return pa->s-pb->s;
    return pb->e-pa->e;
}
int main() {
    int n, m, e, i;
    long long v, sv;
    scanf("%d %d %d", &n, &m, &e);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &cow[i].s, &cow[i].e, &cow[i].p);
    }
    qsort(cow, n, sizeof(cow[0]), mycmp);
    // memset(dp, 0xff, sizeof(dp));
    // gn = n; ge = e; gs = m;
    // dfs(0);
    int ce, j;
    for (i=n-1; i>=0; i--) {
        if (cow[i].e >= e) { dp[i] = cow[i].p; continue; }
        sv = -1;
        ce = cow[i].e+1;
        for (j=i+1; j<n; j++) {
            if (cow[j].s > ce) break;
            if (cow[j].e < ce) continue;
            v = dp[j];
            if (sv<0 || (v>=0 && v<sv)) sv =v ;
        }
        if (sv>0) sv += cow[i].p;
        dp[i] = sv;
    }
    v = -1;
    for (i=0; i<n; i++) {
        if (cow[i].s > m) break;
        if (dp[i]<0) continue;
        if (v<0 || v>dp[i]) v = dp[i];
    }
    printf("%lld\n", v);
    return 0;
}
