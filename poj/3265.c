#include<stdio.h>
#include<string.h>

int as[300], bs[300];
int dp[1001][300];
int gm, gn;
int dfs(int m, int s) {
    if (s==gn) return 1;
    if (dp[m][s] != -1) return dp[m][s];
    int r=-2;
    if (m<gm) r = 1+dfs(gm, s);
    int s1 = 0, s2 = 0;
    int nr, i; for (i=s; i<gn; i++) {
        s1 += as[i];
        s2 += bs[i];
        if (s1>m || s2>gm) break;
        nr = 1+dfs(gm-s2, i+1);
        if (r<0 || r>nr) r = nr;
    }
    dp[m][s] = r;
    return r;
}
int main() {
    int m, p, i;
    scanf("%d %d", &m, &p);
    for (i=0; i<p; i++) scanf("%d %d", &as[i], &bs[i]);
    memset(dp, 0xff, sizeof(dp));
    gm = m; gn = p;
    i = dfs(m, 0);
    printf("%d\n", i+1);
    return 0;
}
