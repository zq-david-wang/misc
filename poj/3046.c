#include<stdio.h>

int cs[1001];
int dp[100001];
int main() {
    int t, a, s, b, i, id;
    scanf("%d %d %d %d", &t, &a, &s, &b);
    for (i=1; i<=t; i++) cs[i] = 0;
    for (i=0; i<a; i++) {
        scanf("%d", &id);
        cs[id]++;
    }
    int ts, k, j;
    for (i=1; i<=b; i++) dp[i] = 0;
    dp[0] = 1;
    for (i=t; i>=1; i--) {
        if (cs[i]==0) continue;
        for (j=b; j>=0; j--) {
            k = cs[i];
            ts = 0;
            if (k>j)k=j;
            for (;k>=0; k--) {
                ts += dp[j-k];
                ts %= 1000000;
            }
            dp[j] = ts;
        }
    }
    int s1 = 0;
    for (i=s; i<=b; i++) {
        s1 += dp[i];
        s1 %= 1000000;
    }
    printf("%d\n", s1);
    return 0;
}
