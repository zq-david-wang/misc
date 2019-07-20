#include<stdio.h>
#include<string.h>

int dp[4096][12];
int map[12];
int gcm[4096];
int gn, gm, gc;
#define MOD 100000000

void dfs2(int s, int cm) {
    gcm[gc++] = cm;
    int i; for (i=s; i<gn; i++) {
        dfs2(i+2, cm|(1<<i));
    }
}
int dfs(int m, int s) {
    if (s==gm) return 1;
    if (dp[m][s] != -1) return dp[m][s];
    int nm, r = 0;
    int i; for (i=0; i<gc; i++) {
        nm = gcm[i];
        if ((nm & map[s] & (~m)) == nm) r += dfs(nm, s+1);
        r %= MOD;
    }
    dp[m][s] = r;
    // printf("dfs %d,%d==>%d\n", m, s, r);
    return r;
}
int main() {
    int m, n, i, j, v, b;
    scanf("%d %d", &m, &n);
    for (i=0; i<m; i++) {
        v = 0;
        for (j=0; j<n; j++) {
            scanf("%d", &b);
            // b = (b+1)&1;
            v = v*2+b;
        }
        map[i] = v;
    }
    memset(dp, 0xff, sizeof(dp));
    gn = n;
    gm = m;
    gc = 0;
    dfs2(0, 0);
    i = dfs(0, 0);
    printf("%d\n", i);
    return 0;
}
