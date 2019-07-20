#include<stdio.h>
#include<string.h>

char ts[1000];
int imc[2][1001];
int dp[2][1000][30];
int gt;
int dfs(int s, int t, int w) {
    if (w==0) return imc[s][t];
    if (t>=gt) return 0;
    if (dp[s][t][w] != -1) return dp[s][t][w];
    int r = 0;
    if (ts[t] == s ) {
        r = 1;
    }
    int c1 = dfs(s, t+1, w);
    int c2 = dfs((s+1)&1, t+1, w-1);
    if (c1<c2)c1 = c2;
    c1+=r;
    dp[s][t][w] = c1;
    return c1;
}
int main() {
    int t, w, i, s;
    scanf("%d %d", &t, &w);
    for (i=0; i<t; i++) {
        scanf("%d", &s); s--;
        ts[i] = s;
    }
    imc[0][t] = 0;
    imc[1][t] = 0;
    for (i=t-1; i>=0; i--) {
        s = ts[i];
        imc[s][i] = imc[s][i+1] + 1;
        s = (s+1) &1;
        imc[s][i] = imc[s][i+1];
    }
    gt = t;
    memset(dp, 0xff, sizeof(dp));
    s = dfs(0, 0, w);
    i = dfs(1, 0, w);
    if (s<i) s=i;
    printf("%d\n", s);
    return 0;
}
