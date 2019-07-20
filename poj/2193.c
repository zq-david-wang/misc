#include<stdio.h>
#include<string.h>

long long dp[2001][12];
int gm;
long long dfs(int s, int n) {
    if (n==0) return 1;
    if (s>gm) return 0;
    if (dp[s][n] != -1) return dp[s][n];
    long long r = dfs(s+1, n) + dfs(s*2, n-1);
    dp[s][n]=r;
    return r;
}
int main() {
    int c, i, n, m;
    long long r;
    scanf("%d", &c); for (i=1; i<=c; i++) {
        scanf("%d %d\n", &n, &m);
        memset(dp, 0xff, sizeof(dp));
        gm = m;
        r = dfs(1, n);
        printf("Case %d: n = %d, m = %d, # lists = %lld\n", i, n, m, r);
    }
    return 0;
}
