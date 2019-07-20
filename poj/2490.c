#include<stdio.h>
#include<string.h>

int cost[14][14];
int dp[1024*16];
int accu[14][1024*16];

int calc(int i, int s, int n) {
    if (accu[i][s] != -1) return accu[i][s];
    int j, c = 0;
    for (j=0; j<n; j++) {
        if (s&(1<<j)) c += cost[i][j];
    }
    accu[i][s] = c;
    return c;
}
int dfs(int s, int n) {
    if (dp[s]!=-1) return dp[s];
    int c, mc = -1;
    int i, m=1; for (i=0; i<n; i++) {
        if ((s&m) == 0) {
            c = cost[i][i]+calc(i, s, n) + dfs(s|m, n);
            if (mc==-1 || mc>c)mc = c;
        }
        m<<=1;
    }
    if (mc<0) mc = 0;
    dp[s] = mc;
    return mc;
}
int main() {
    int c, i, n, j, k;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        printf("Scenario #%d:\n", i);
        scanf("%d", &n);
        for (j=0; j<n; j++) for (k=0; k<n; k++) scanf("%d", &cost[j][k]);
        memset(dp, 0xff, (1<<n)*(sizeof(int)));
        for (j=0; j<n; j++) memset(accu[j], 0xff, (1<<n)*sizeof(int));
        dp[(1<<n)-1] = 0;
        k = dfs(0, n);
        printf("You have officially been pimped for only $%d\n", k);
        printf("\n");
    }
    return 0;
}
