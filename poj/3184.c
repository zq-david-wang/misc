#include<stdio.h>

int ps[10000];
int dp[10004];
int main() {
    int n, l, i, j;
    scanf("%d %d", &n, &l);
    if (n==1) {
        printf("0\n");
        return 0;
    }
    for (i=0; i<n; i++) scanf("%d", &ps[i]);
    int d, c;
    d = (l+1-n)/(n-1)+1;
    c = (l+1-n) % (n-1);
    dp[c] = 0;
    dp[c+1] = -1;
    for (i=0; i<c; i++) dp[i] = -1;
    int v, x, dx, v1;
    for (i=n-1; i>0; i--) {
        for (j=0; j<=c && j<i; j++) {
            x = (i-1)*d+j;
            v = -1;
            if (dp[j]>=0) {
                dx = ps[i]-(x+d);
                if (dx<0) dx = -dx;
                v =  dp[j]+dx;
            }
            if (dp[j+1]>=0) {
                dx = ps[i]-(x+d+1);
                if (dx<0) dx = -dx;
                v1 = dp[j+1]+dx;
                if (v<0 || v>=v1) v = v1;
            }
            dp[j] = v;
        }
    }
    v = dp[0]+ps[0];
    printf("%d\n", v);
    return 0;
}
