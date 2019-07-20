#include<stdio.h>
#include<string.h>

char steps[][2] = {
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

int map[51][51];
char flag[52][52];
struct { short n, p; char r, c, s; } pool[60000];
int pc;
short nei[52][52];
char smap[52][52][52][52];
struct { char r, c; } path[52][52];
int dfs(int sr, int sc, int er, int ec) {
    if (sr==er&&sc==ec) return 1;
    int j = nei[sr][sc], nr, nc;
    while(j!=-1) {
        nr = pool[j].r;
        nc = pool[j].c;
        if (smap[sr][sc][nr][nc] && flag[nr][nc]==0) {
            path[nr][nc].r= sr;
            path[nr][nc].c= sc;
            flag[nr][nc]=1;
            if (dfs(nr, nc, er, ec)) return 1;
        }
        j = pool[j].n;
    }
    return 0;
}
int findpath(int sr, int sc, int er, int ec) {
    memset(flag, 0, sizeof(flag));
    flag[sr][sc]=1;
    return dfs(sr, sc, er, ec);
}
int maxflow(int sr, int sc, int er, int ec) {
    int f, rc=0, r, c, ar, ac;
    while(1) {
        f = findpath(sr, sc, er, ec);
        if (f==0) break;
        rc += f;
        r = er; c=ec;
        while(r!=sr&&c!=sc) {
            ar = path[r][c].r;
            ac = path[r][c].c;
            smap[ar][ac][r][c]=0;
            smap[r][c][ar][ac]=1;
            r=ar; c=ac;
        }
    }
    return rc;
}
int main() {
    int r, c, i, j, ni, nj;
    int v, k, c1, c2, ic=0;
    int head, tail, cc, ci, cj, nn;
    while(1) {
        scanf("%d %d", &r, &c); if (r==0) break;
        ic++; pc=0; 
        for (i=1; i<=r; i++) for (j=1; j<=c; j++) scanf("%d", &map[i][j]);
        memset(nei, 0xff, sizeof(nei));
        memset(smap, 0, sizeof(smap));
        for (i=1; i<=r; i++) for (j=1; j<=c; j++) {
            if (map[i][j]<0) { continue; }
            v = map[i][j];
            for (k=0; k<12; k++) {
                if (v&(1<<k)) {
                    ni = i+steps[k][0];
                    nj = j+steps[k][1];
                    if (ni<1||ni>r||nj<1||nj>c) continue;
                    if (map[ni][nj]<0) continue;
                    if (smap[i][j][ni][nj]||smap[ni][nj][i][j]) continue;
                    pool[pc].r=i; pool[pc].c=j; pool[pc].n=nei[ni][nj]; nei[ni][nj]=pc++;
                    pool[pc].r=ni; pool[pc].c=nj; pool[pc].n=nei[i][j]; nei[i][j]=pc++;
                    if ((i+j)&1) { smap[ni][nj][i][j]=1; }
                    else { smap[i][j][ni][nj]=1; }
                }
            }
            if ((i+j)&1) {
                smap[i][j][r+1][c+1]=1;
                pool[pc].r=r+1; pool[pc].c=c+1; pool[pc].n=nei[i][j]; nei[i][j]=pc++;
                pool[pc].r=i; pool[pc].c=j; pool[pc].n=nei[r+1][c+1]; nei[r+1][c+1]=pc++;
            } else {
                smap[0][0][i][j]=1;
                pool[pc].r=0; pool[pc].c=0; pool[pc].n=nei[i][j]; nei[i][j]=pc++;
                pool[pc].r=i; pool[pc].c=j; pool[pc].n=nei[0][0]; nei[0][0]=pc++;
            }
        }
        k = maxflow(0,0, r+1, c+1);
        printf("%d. %d\n", ic, k);
    }
    return 0;
}
