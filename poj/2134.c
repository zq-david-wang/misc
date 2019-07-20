#include<stdio.h>
#include<string.h>

#define MS 12
#define MTIME 1110
char pass[101][MTIME+10];
int dp[MTIME+10][101][MS+1];
int dp2[MTIME+10][101];
int gl;

int maxd(int t, int p) {
    if (p==gl) return 0;
    if (dp2[t][p] != -1) return dp2[t][p];
    int r = 0;
    if (pass[p][t]) r = 1+maxd(t,p+1);
    dp2[t][p] = r;
    return r;
}
int dfs(int t, int p, int v) {
    if (p>gl) return -2;
    if (p==gl) {
        if (v<=1) return 0;
        return -2;
    }
    if (t>=MTIME) return -2;
    if (v<0) return -2;
    if (v>MS) return -2;
    if (dp[t][p][v] != -1) return dp[t][p][v];
    int md = maxd(t, p);
    int r = -2, tr;
    if (md>=v) {
        tr = dfs(t+1, p+v, v);
        if (tr>=0) { tr++; if (r<0||r>tr)r=tr; }
        tr = dfs(t+1, p+v, v+1);
        if (tr>=0) { tr++; if (r<0||r>tr)r=tr; }
        tr = dfs(t+1, p+v, v-1);
        if (tr>=0) { tr++; if (r<0||r>tr)r=tr; }
    }
    dp[t][p][v] = r;
    return r;
}

int main() {
    int l, n, i, t;
    int p, tg, tr, tc;
    char ic[8], f;
    scanf("%d %d", &l, &n);
    memset(pass, 1, sizeof(pass));
    for (i=0; i<n; i++) {
        scanf("%d %d %d %s %d", &p, &tg, &tr, ic, &tc);
        f=1; if (ic[0]=='R')f=0;
        for (t=0; t<=MTIME; t++) {
            if (f==0 && tc == tr) {
                f=1; tc=0;
            } else if (f==1 && tc==tg) {
                f=0; tc=0;
            }
            pass[p][t] = f;
            tc++;
        }
    }
    gl = l;
    memset(dp, 0xff, sizeof(dp));
    memset(dp2, 0xff, sizeof(dp2));
    i = dfs(0, 0, 0);
    printf("%d\n", i);
    return 0;
}
