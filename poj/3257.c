#include<stdio.h>
#include<string.h>

typedef struct _T {
    struct _T *n;
    int w, f, c;
}ENode;
ENode *loc[1001];
ENode gpool[10000];
int dp[1001][1001];
int gl;
int dfs(int s, int b) {
    if (s>=gl) return 0;
    if (dp[s][b] !=-1) return dp[s][b];
    int r = -2, tr;
    ENode *p = loc[s];
    while(p!=NULL) {
        if (b>=p->c) {
           tr = dfs(s+p->w, b-p->c);
           if (tr>=0) {
               tr += p->f;
               if (r<tr) r = tr;
           }
        }
        p = p->n;
    }
    dp[s][b] = r;
    return r;
}
int main() {
    int l, n, b, i;
    scanf("%d %d %d", &l, &n, &b);
    int x, w, f, c;
    for (i=0; i<=l; i++) loc[i] = NULL;
    for (i=0; i<n; i++) {
        scanf("%d %d %d %d", &x, &w, &f, &c);
        gpool[i].w = w; gpool[i].f = f; gpool[i].c = c;
        gpool[i].n = loc[x];
        loc[x] = &gpool[i];
    }
    memset(dp, 0xff, sizeof(dp));
    gl = l;
    i = dfs(0, b);
    if (i<0)i=-1;
    printf("%d\n", i);
    return 0;
}
