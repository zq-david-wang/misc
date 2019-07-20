#include<stdio.h>

int utils[4000];
int dp[3834][2];

int main() {
    int n, i, j, b, mu=0, v1, v2, v;
    scanf("%d %d", &n, &b);
    for (i=0; i<n; i++) scanf("%d", &utils[i]);
    // set last day to sleep
    for (i=0; i<b; i++) {
        dp[i][1] = utils[n-1];
        dp[i][0] = 0;
    }
    for (i=n-2; i>=0; i--) {
        for (j=b-1; j>0; j--) {
            v1 = dp[j][0];
            v2 = dp[j-1][1];
            v = v1; if (v<v2) v = v2;
            dp[j][0] = v;
            v2 += utils[i];
            if (v<v2) v = v2;
            dp[j][1] = v;
        }
        dp[0][0] = 0;
        dp[0][1] = 0;
    }
    mu = dp[b-1][1];
    for (i=0; i<=b; i++) {
        dp[i][1] = 0;
        dp[i][0] = 0;
    }
    for (i=n-2; i>=0; i--) {
        for (j=b; j>0; j--) {
            v1 = dp[j][0];
            v2 = dp[j-1][1];
            v = v1; if (v<v2) v = v2;
            dp[j][0] = v;
            v2 += utils[i];
            if (v<v2) v = v2;
            dp[j][1] = v;
        }
        dp[0][0] = 0;
        dp[0][1] = 0;
    }
    if (mu<dp[b][0]) mu = dp[b][0];
    printf("%d\n", mu);
    return 0;
}
