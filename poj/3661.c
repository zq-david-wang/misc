#include<stdio.h>

int ds[10000];
int dp[10001][501];
int main() {
    int n, m, i, v, v1, j;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; i++) scanf("%d", &ds[i]);
    for (i=1; i<=m; i++) dp[n][i] = -1; dp[n][0] = 0;
    for (i=n-1; i>=0; i--) {
        for (j=0; j<=m; j++) {
            if (i+j>n) { dp[i][j] = -1; continue; }
            v = dp[i+j+(j==0)][0];
            if (j<m) {
                v1 = dp[i+1][j+1];
                if (v1>=0) {
                    v1 += ds[i];
                    if (v<0 || v<v1) v = v1;
                }
            }
            dp[i][j] = v;
        }
    }
    printf("%d\n", dp[0][0]);
    return 0;
}
