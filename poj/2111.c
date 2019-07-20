#include<stdio.h>
#include<string.h>

int board[365][365];
int dp[365][365];
int rows[365][365];
int cols[365][365];
int gn;
char dir[8][2] = {
    {1, 2},
    {1, -2},
    {2, 1},
    {2, -1},
    {-1, -2},
    {-1, 2},
    {-2, -1},
    {-2, 1},
};
int dfs(int r, int c) {
    if (dp[r][c] != -1) return dp[r][c];
    int p = 0, nr, nc, cr=-1, cc=-1;
    int i, cp; for (i=0; i<8; i++) {
        nr = r+dir[i][0];
        nc = c+dir[i][1];
        if (nr<0||nr>=gn||nc<0||nc>=gn) continue;
        if (board[nr][nc]<= board[r][c]) continue;
        cp = 1+dfs(nr, nc);
        if (p<cp || (p==cp && board[nr][nc]<board[cr][cc])) {
            p = cp; cr = nr; cc = nc;
        }
    }
    dp[r][c] = p;
    rows[r][c] = cr;
    cols[r][c] = cc;
    return p;
}
int main() {
    int n, i, j;
    scanf("%d", &n);
    gn = n;
    for (i=0; i<n; i++) for (j=0; j<n; j++) scanf("%d", &board[i][j]);
    memset(dp, 0xff, sizeof(dp));
    int mp=-1, mi, mj, p;
    for (i=0; i<n; i++) for (j=0; j<n; j++) {
        p = dfs(i, j);
        if (mp<p || (mp==p&&board[i][j]<board[mi][mj])) {
            mp = p;
            mi = i; mj = j;
        } 
    }
    printf("%d\n", mp+1);
    int ni, nj;
    while(dp[mi][mj]) {
        printf("%d\n", board[mi][mj]);
        ni = rows[mi][mj];
        nj = cols[mi][mj];
        mi = ni; mj = nj;
    }
    printf("%d\n", board[mi][mj]);
    return 0;
}
