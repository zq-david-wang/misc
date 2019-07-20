#include<stdio.h>
#include<string.h>

long long dp[19][201];
long long dfs(int n, int k) {
    if (n==0) return 0;
    if (k==0) return 1;
    if (dp[n][k]!=-1) return dp[n][k];
    long long r;
    int c = n*(n-1)/2;
    if (k>c) r= 0;
    else if (k==c) r=1;
    else {
        r = 0;
        int i; for (i=1; i<=n; i++) {
            if (i-1<=k) { 
                r += dfs(n-1, k-(i-1));
            }
        }
    }
    dp[n][k]=r;
    return r;
}
int main() {
    int n, k;
    long long r;
    memset(dp, 0xff, sizeof(dp));
    while(1) {
        scanf("%d %d", &n, &k); if (n==0) break;
        r = dfs(n, k);
        printf("%lld\n", r);
    }
    return 0;
}
