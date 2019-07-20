#include<stdio.h>
#include<string.h>
#include<math.h>

char dp[40+1][40*40/3+8][40*40/2+8];
int seg[40];
int gs, gn, g1, g2;
long long garea;
void dfs(int s, int s1, int s2) {
    if (s>gn) return;
    if (dp[s][s1][s2]) return;
    int s3 = gs-s1-s2;
    if (s1>0 && s1<=s2 && s2<=s3) {
        if (s1+s2>s3) {
            int v = (gs-s1-s1)*(gs-s2-s2)*(gs-s3-s3);
            if (v>garea) garea=v;
        }
    }
    dp[s][s1][s2] = 1;
    if (s==gn) return;
    if (s1+seg[s]<=g1) {
        dfs(s+1, s1+seg[s], s2);
    }
    if (s2+seg[s]<=g2) {
        dfs(s+1, s1, s2+seg[s]);
    }
    dfs(s+1, s1, s2);
}
int main() {
    int n, i, s=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &seg[i]);
        s += seg[i];
    }
    gs=s; gn=n; garea=-1; g1=s/3; g2=s/2;
    memset(dp, 0, sizeof(dp));
    dfs(0, 0, 0);
    if (garea>0) {
        double r = sqrt(garea*s); r*=25;
        // garea = floor(r)+0.1;
        garea = r;
    }
    printf("%lld\n", garea);
    return 0;
}
