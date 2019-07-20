#include<stdio.h>
#include<string.h>

char ws[312];
char dict[600][32];
short pos[301][26];
int dp[300];
int dp2[600][300];
int len[600];
int dfs2(int di, int s) {
    if (dp2[di][s] != -1) return dp2[di][s];
    int i, lw = len[di], r = -2;
    int ns = s;
    for (i=0; i<lw; i++) {
        ns = pos[ns][dict[di][i]-'a'];
        if (ns<0) break;
        ns++;
    }
    if (i<lw) r = -2;
    else r = ns;
    dp2[di][s] = r;
    return r;
}
int dfs(int s, int l, int w) {
    if (s==l) return 0;
    if (s>l) return -2;
    if (dp[s] != -1) return dp[s];
    int r = l-s, ns, nc;
    int i; for (i=0; i<w; i++) {
        ns = dfs2(i, s);
        if (ns<0) continue;
        nc = dfs(ns, l, w);
        if (nc<0) continue;
        nc += (ns-s-len[i]);
        if (r>nc) r = nc;
    }
    dp[s] = r;
    return r;
}
int main() {
    int w, l, i, j;
    scanf("%d %d", &w, &l);
    scanf("%s", ws);
    for (i=0; i<w; i++) {
        scanf("%s", dict[i]);
        len[i] = strlen(dict[i]);
    }
    for (i=0; i<26; i++) pos[l][i] = -1;
    for (i=l-1; i>=0; i--) {
        for (j=0; j<26; j++) pos[i][j] = pos[i+1][j];
        pos[i][ws[i]-'a'] = i;
    }
    memset(dp, 0xff, sizeof(dp));
    memset(dp2, 0xff, sizeof(dp2));
    i = dfs(0, l, w);
    printf("%d\n", i);
    return 0;
}
