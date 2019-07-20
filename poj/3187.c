#include<stdio.h>

int cs[11][10];
int num[16];
char flag[16];
int gn, gs;
int dfs(int s, int m) {
    if (m>gs) return 0;
    if (s==gn) {
        if (m==gs) return 1;
        return 0;
    }
    int i, r; for (i=1; i<=gn; i++) {
        if (flag[i]) continue;
        flag[i] = 1;
        num[s] = i;
        r = dfs(s+1, m+i*cs[gn][s]);
        if (r) return 1;
        flag[i] = 0;
    }
    return 0;
}

int main() {
    int i, j, n, s;
    for (i=1; i<=10; i++) {
        cs[i][0] = 1;
        cs[i][i-1] = 1;
        for (j=1; j<i-1; j++) {
            cs[i][j] = cs[i-1][j-1]+cs[i-1][j];
        }
    }
    scanf("%d %d", &n, &s);
    for (i=1; i<=n; i++) flag[i] = 0;
    gn = n; gs = s;
    dfs(0, 0);
    for (i=0; i<n; i++) {
        if (i>0) printf(" %d", num[i]);
        else printf("%d", num[i]);
    }
    printf("\n");
    return 0;
}
