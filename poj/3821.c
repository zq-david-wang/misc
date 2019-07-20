#include<stdio.h>
#include<string.h>

char dp[256][256];
char buf[256];
char dfs(int s, int e) {
    if (s>e) return 1;
    if (s==e) return 0;
    if (dp[s][e]!=-1) return dp[s][e];
    char r=0;
    int i, j, k1, k2; for (i=s+2; i+1<=e; i++) {
        if (dfs(s, i-1) && dfs(i, e)) r=1;
        if (r) break;
    }
    if (r==0 && buf[s]==buf[e]) {
        r = dfs(s+1, e-1);
        if (r==0) {
            for (i=s+1; i<e; i++) if (buf[i]==buf[s] && dfs(s+1, i-1) && dfs(i+1, e-1)) { r=1; break; }
        }
    }
    dp[s][e]=r;
    return r;
}
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    return i;
}
int main() {
    int l, i;
    while(l=readline()) {
        memset(dp, 0xff, sizeof(dp));
        for (i=0; i<l; i++) if (buf[i]>'Z'||buf[i]<'A') break;
        if (i==l && dfs(0, l-1)) printf("solvable\n");
        else printf("unsolvable\n");
    }
    return 0;
}
