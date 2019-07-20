#include<stdio.h>

int rows[350][350];
int dp[351][351];

int main() {
    int n, i, j, k;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        for (j=0; j<=i; j++) scanf("%d", &rows[i][j]);
    }
    for (i=0; i<=n; i++) dp[n][i] = 0;
    for (i=n-1; i>=0; i--) {
        for (j=0; j<=i; j++) {
            k = dp[i+1][j];
            if (k<dp[i+1][j+1]) k = dp[i+1][j+1];
            dp[i][j] = k+rows[i][j];
        }
    }
    printf("%d\n", dp[0][0]);
    return 0;
}
