#include<stdio.h>
#include<string.h>


char dp[20][101][101];
int gn, ge, gd;
char dfs(int s, int e, int d) {
    if (d<=0) return 0;
    if (s==gn) return -2;
    if (dp[s][e][d] != -1) return dp[s][e][d];
    char r = dfs(s+1, ge-(gd-d), d), t, v;
    int i; for (i=1; i<=10; i++) {
        v = i*i;
        if (v>e) break;
        t = dfs(s, e-v, d-i);
        if (t>=0) {
            t++;
            if (r<0 || r>t) r = t;
        }
    }
    dp[s][e][d] = r;
    return r;
}
int main() {
    int n, e, d;
    memset(dp, 0xff, sizeof(dp));
    scanf("%d %d %d\n", &n, &e, &d);
    gn = n; ge = e; gd = d;
    char r = dfs(0, e, d);
    if (r<0) r = 0; 
    printf("%d\n",  r);
    return 0;
}
