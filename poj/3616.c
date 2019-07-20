#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { int s, e, f; }SNode;
SNode seg[1000];
int dp[1000001];
int si[1000002];
int gn, gr, gm;
int mycmp(const void* a, const void *b) {
    return ((const SNode*)a)->s - ((const SNode*)b)->s;
}
int dfs(int s) {
    if (s>gn) return 0;
    if (dp[s] != -1) return dp[s];
    int i, r=0, t;
    for (i=si[s]; i<gm; i++) {
        t = dfs(seg[i].e+gr) + seg[i].f;
        if (t>r) r = t;
    }
    dp[s] = r;
    return r;
}
int main() {
    int n, m, r, i, j;
    scanf("%d %d %d", &n, &m, &r);
    for (i=0; i<m; i++) scanf("%d %d %d", &seg[i].s, &seg[i].e, &seg[i].f);
    qsort(seg, m, sizeof(seg[0]), mycmp);
    j=m-1; for (i=n; i>=0; i--) {
        while(j>=0) {
            if (seg[j].s < i) break;
            j--;
        }
        si[i] = j+1;
    }
    memset(dp, 0xff, sizeof(dp));
    gn = n; gr = r; gm = m;
    i = dfs(0);
    printf("%d\n", i);
    return 0;
}
