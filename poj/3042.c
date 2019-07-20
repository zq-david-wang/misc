#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int *)b);
}
long long dp[1000][1000][2];
int gn;
int pos[1000];
long long dfs(int i, int c, int s) {
    if (c==gn) return 0;
    if (dp[i][c][s] != -1) return dp[i][c][s];
    long long r = -1, tr;
    if (s==0) {
        if (i>0) r = (gn-c)*(pos[i]-pos[i-1]) + dfs(i-1, c+1, 0);
        if (i+c<gn) {
            tr = (gn-c)*(pos[i+c]-pos[i]) + dfs(i+c, c+1, 1);
            if (r==-1 || r>tr) r=tr;
        }
    } else {
        if (i-c>=0) r = (gn-c)*(pos[i]-pos[i-c]) + dfs(i-c, c+1, 0);
        if (i+1<gn) {
            tr = (gn-c)*(pos[i+1]-pos[i]) + dfs(i+1, c+1, 1);
            if (r==-1||r>tr) r = tr;
        }
    }
    dp[i][c][s] = r;
    return r;
}
int main() {
    int n, l, i;
    long long ml=-1, tl;
    scanf("%d %d", &n, &l);
    for (i=0; i<n; i++) scanf("%d", &pos[i]);
    qsort(pos, n, sizeof(pos[0]), mycmp);
    memset(dp, 0xff, sizeof(dp));
    for (i=0; i<n; i++) if (pos[i]>=l) break;
    // dp[i][c][0] = max((n-c)*(pos[i]-pos[i-1]) + dp[i-1][c+1][0], (n-c)*(pos[i+c]-pos[i])+dp[i+c][c+1][1]
    gn = n;
    if (i>0) ml = (l-pos[i-1])*n + dfs(i-1, 1, 0);
    if (i<n) {
        tl = (pos[i]-l)*n + dfs(i, 1, 1);
        if (ml==-1 || ml>tl) ml = tl;
    }
    printf("%lld\n", ml);
    return 0;
}
