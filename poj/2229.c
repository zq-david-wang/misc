#include<stdio.h>

int dp[1000001];

int main() {
    int n, i;
    scanf("%d", &n);
    dp[0] = 0; dp[1] = 1;
    for (i=2; i<=n; i++) {
        dp[i] = dp[i-1];
        if ((i%2)==0) dp[i] += dp[i/2];
        dp[i] %= 1000000000;
    }
    printf("%d\n", dp[n]);
    return 0;
}
