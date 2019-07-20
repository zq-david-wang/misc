#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ws[256];
char mark[256][256];
int dp[256][256];
int gn, gs;
#define INF 0x7fffffff
int dfs(int s, int t) {
    if (s>=gn) return 0;
    if (t==0) return INF;
    if (mark[s][t]) return dp[s][t];
    int r = INF, i, v;
    for (i=1; i<=gs; i++) {
        v = dfs(s+i, t-1);
        if (v==INF) continue;
        if (s+i<gn) v+=ws[s+i];
        if (r==INF||r<v) r=v;
    }
    mark[s][t]=1;
    dp[s][t]=r;
    return r;
}
int main() {
    int n, s, t, i;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        scanf("%d %d", &s, &t);
        for (i=1; i<=n; i++) scanf("%d", &ws[i]);
        gn=n+1; gs=s;
        memset(mark, 0, sizeof(mark));
        i = dfs(0, t);
        printf("%d\n", i);
    } 
    return 0;
}


