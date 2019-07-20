#include<stdio.h>
#include<string.h>

char name[2004];
int cost[26];
int dp[2000][2000];
#define INF 0x7fffffff
int dfs(int s, int e) {
    if (s>=e) return 0;
    if (dp[s][e]!=-1) return dp[s][e];
    int r = INF, v;
    if (name[s]==name[e]) {
        r = dfs(s+1, e-1);
    } else {
        v = dfs(s+1, e) + cost[name[s]-'a'];
        if (r>v) r = v;
        v = dfs(s, e-1) + cost[name[e]-'a'];
        if (r>v) r = v;
    }
    dp[s][e] = r;
    return r;
}
int main() {
    int n, m, i, ii;
    int ac, dc;
    char b[8];
    scanf("%d %d", &n, &m);
    scanf("%s", name);
    for (i=0; i<n; i++) {
        scanf("%s %d %d", b, &ac, &dc);
        ii = b[0]-'a';
        if (ac>dc) ac = dc;
        cost[ii] = ac;
    }
    memset(dp, 0xff, sizeof(dp));
    i = dfs(0, m-1);
    printf("%d\n", i);
    return 0;
}
