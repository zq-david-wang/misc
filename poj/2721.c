#include<stdio.h>
#include<string.h>


int dp[32][32];
int calc(int a, int b) {
    if (a==b||a==0) return 1;
    if (dp[a][b]!=-1) return dp[a][b];
    int r = calc(a, b-1)+calc(a-1, b-1);;
    dp[a][b]=r;
    return r;
}
int main() {
    int a, b, i, t, c;
    double r;
    memset(dp, 0xff, sizeof(dp));
    while(1) {
        scanf("%d %d", &a, &b); if (a==-1) break;
        t=0; for (i=0; i<=a+b; i++) {
            t+=calc(i, a+b)*calc(13-i, 26-a-b);
        } 
        c = calc(a, a+b)*calc(13-a, 26-a-b);
        if (a!=b) c+=calc(b, a+b)*calc(13-b, 26-a-b);
        r = c; r/=t;
        printf("%d-%d split: %.8f\n", a, b, r);     
    }
    return 0;
}
