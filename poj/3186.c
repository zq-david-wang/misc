#include<stdio.h>

int ts[2000];
int sum[2000][2000];
int dp[2000][2000];

int main() {
    int n, i, d, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &ts[i]);
    for (i=0; i<n; i++) {
        d = 0;
        for (j=i; j<n; j++) {
            d += ts[j];
            sum[i][j] = d;
        }
    }
    for (i=0; i<n; i++) dp[i][0] = ts[i];
    for (d=1; d<n; d++) {
        for (i=0; i+d<n; i++) {
            dp[i][d] = dp[i+1][d-1]+sum[i+1][i+d]+ts[i];
            j = dp[i][d-1]+sum[i][i+d-1]+ts[i+d];
            if (dp[i][d]<j) dp[i][d] = j;
        }
    }
    printf("%d\n", dp[0][n-1]);
    return 0;
}
