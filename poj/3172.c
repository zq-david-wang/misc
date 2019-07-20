#include<stdio.h>
#include<string.h>

int ws[64];
int dp[64][65536];
long long ss[1024];
int gm;
int dfs2(int e, int c) {
    if (e<0) return 0;
    if (dp[e][c] != -1) return dp[e][c];
    if (ss[e]<=c) {
        dp[e][c] = ss[e];
        return ss[e];
    }
    int r = dfs2(e-1, c);
    if (ws[e]<c) {
        int t = dfs2(e-1, c-ws[e])+ws[e];
        if (r<t) r = t;
    }
    dp[e][c] = r;
    return r;
}
void dfs(int e, int c) {
    if (e<0) return;
    int t;
    if (c<=65536) {
        t = c- dfs2(e, c);
        if (t<gm) gm = t;
        return;
    }
    dfs(e-1, c);
    if (ws[e]>c) return;
    if (ss[e]<=c) {
        t = c-ss[e];
        if (t<gm) gm = t;
        return;
    }
    dfs(e-1, c-ws[e]);
}
int main() {
    int n, c, i;
    scanf("%d %d", &n,  &c);
    for (i=0; i<n; i++) scanf("%d", &ws[i]);
    ss[0] = ws[0]; for (i=1; i<n; i++) ss[i] = ss[i-1]+ws[i];
    gm = c;
    memset(dp, 0xff, sizeof(dp));
    dfs(n-1, c);
    printf("%d\n", c-gm);
    return 0;
}
