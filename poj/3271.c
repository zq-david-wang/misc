#include<stdio.h>
#include<string.h>

char map[32][32];
char flag[32][32];
int queue[32*32];
#define MOD 1024
char step[][2] = {
    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
};
long long dp[32][32];
int depth[32][32];
int group[32][32];
long long gdp[32*32];
char gflag[300][32][32];
char tflag[32][32];
char priority[32][32];
#define INF 0x7fffffff

int main() {
    int m, n, i, j, k, v, d, md, nd;
    int sr, sc, dr, dc;
    int ii, jj;
    long long r;
    int dd, ddd, ni, nj, nni, nnj, i1, i2;
    int tg[8], gid, gc, ggid=1;
    scanf("%d %d", &m, &n);
    for (i=0; i<m; i++) for (j=0; j<n; j++) {
        scanf("%d", &v);
        if (v==3) { sr = i; sc = j; v = 1;}
        if (v==4) { dr = i; dc = j; v = 1;}
        map[i][j] = v;
        dp[i][j] = -1;
        depth[i][j] = INF;
        flag[i][j] = 0;
        group[i][j] = -1;
        priority[i][j] = 0;
    }
    depth[dr][dc] = 0;
    memset(gflag, 0, sizeof(gflag));
    while(1) {
        md = INF;
        for (i=0; i<m; i++) for (j=0; j<n; j++) {
            if (flag[i][j]) continue;
            if (depth[i][j]==INF) continue;
            if (md > depth[i][j] || (md==depth[i][j] &&map[i][j]==0) || (md==depth[i][j]&&map[ni][nj]==1&&priority[i][j]==1)) {
                md = depth[i][j];
                ni = i; nj = j;
            }
        }
        if (md==INF) break;
        dp[ni][nj] = 0;
        if (map[ni][nj]==1) {
            gid = -1;
            for (d=0; d<8; d++) {
                nni = ni+step[d][0]; nnj = nj+step[d][1];
                if (nni<0||nni>=m||nnj<0||nnj>=n) continue;
                if (map[nni][nnj]==1) priority[nni][nnj] = 1;
                if (flag[nni][nnj]==0)continue;
                if (depth[nni][nnj] != md) continue;
                if (map[nni][nnj]==1) {
                    // only add the group dp
                    if (gid>=0 && gid != group[nni][nnj]) printf("error\n");
                    gid = group[nni][nnj];
                }
            }
            if (gid==-1) { gid = ggid++; gdp[gid] = 0;}
            group[ni][nj] = gid;
            for (d=0; d<8; d++) {
                nni = ni+step[d][0];
                nnj = nj+step[d][1];
                if (nni<0||nni>=m||nnj<0||nnj>=n) continue;
                if (flag[nni][nnj]==0)continue;
                if (depth[nni][nnj] != md) continue;
                if (map[nni][nnj]==1) continue;
                if (gflag[gid][nni][nnj]==0) {
                    gdp[gid] += dp[nni][nnj];
                    gflag[gid][nni][nnj] = 1;
                }
            }
            // printf("gid:%d(%d,%d) ==> %lld, md:%d\n", gid, ni, nj, gdp[gid], md);
        } else {
            gc = 0;
            memset(tflag, 0, sizeof(tflag));
            for (d=0; d<8; d++) {
                nni = ni+step[d][0];
                nnj = nj+step[d][1];
                if (nni<0||nni>=m||nnj<0||nnj>=n) continue;
                if (flag[nni][nnj]==0)continue;
                if (depth[nni][nnj] != (md-1)) continue;
                if (map[nni][nnj]==1) {
                    // only add the group dp
                    gid = group[nni][nnj];
                    for (ii=0; ii<m; ii++) for (jj=0; jj<n; jj++) {
                        if (gflag[gid][ii][jj]) tflag[ii][jj] = 1;
                    }
                } else tflag[nni][nnj] = 1;
            }
            for (ii=0; ii<m; ii++) for (jj=0; jj<n; jj++) {
                if (tflag[ii][jj]) dp[ni][nj] += dp[ii][jj];
            }
            if (dp[ni][nj]==0) dp[ni][nj] = 1;
        }
        // printf("dp %d,%d --> %lld\n", ni, nj, dp[ni][nj]);
        flag[ni][nj] = 1;
        for (d=0; d<8; d++) {
            nni = ni+step[d][0];
            nnj = nj+step[d][1];
            if (nni<0||nni>=m||nnj<0||nnj>=n) continue;
            if (map[nni][nnj] == 2) continue;
            if (flag[nni][nnj]) continue;
            nd = md; if (map[nni][nnj]==0) nd++;
            if (nd<depth[nni][nnj])depth[nni][nnj] = nd;
        }

    }
    if (depth[sr][sc] == 0) {
        printf("0\n1\n");
    } else {
        gid = group[sr][sc];
        if (gid < 0) printf("-1\n");
        else {
            long long s = 0;
            for (i=0; i<m; i++) for (j=0; j<n; j++) {
                if (gflag[gid][i][j]) s += dp[i][j];
            }
            printf("%d\n%lld\n", depth[sr][sc], s);
        }
    }
    return 0;
}
