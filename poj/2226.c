#include<stdio.h>
#include<string.h>

char map[64][64];
char smap[25*50*2+4][25*50*2+4];
short nei[25*50*2+4][25*50*2+4];
short neic[25*50*2+4];
char flow[25*50*2+4][25*50*2+4];
char flag[25*50*2+4];
short rid[64][64], cid[64][64];
short path[25*50*2+4];
int dfs(int s, int e) {
    if (s==e) return 1;
    int i, r, b; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[s][b]) continue;
        if (flow[b][s]==1 || smap[s][b]==1) {
            flag[b] = 1;
            path[b] = s;
            r = dfs(b, e);
            if (r) return r;
        }
    }
    return 0;
}
int findpath(int e) {
    memset(flag, 0, (e+1)*sizeof(flag[0]));
    flag[0] = 1;
    return dfs(0, e);
}
int maxflow(int e) {
    int r = 0, f;
    int a, b;
    memset(flow, 0, sizeof(flow));
    while(1) {
        f = findpath(e);
        // printf("find path: %d\n", f);
        if (f==0) break;
        // apply path
        b = e;
        while(b != 0) {
            a = path[b];
            if (smap[a][b]==0) flow[b][a] = 0;
            else flow[a][b] = 1;
            b = a;
        }
        r += f;
    }
    return r;
}
int main() {
    int r, c, i, j;
    int g1, g2;
    scanf("%d %d", &r, &c);
    for (i=0; i<r; i++) scanf("%s", map[i]);
    int gid = 1, rg;
    for (i=0; i<r; i++) {
        for (j=0; j<c; j++) {
            if (map[i][j]=='*') rid[i][j] = gid;
            else if (j>0 && map[i][j-1]=='*') gid++;
        }
        if (map[i][c-1]=='*') gid++;
    }
    rg = gid;
    for (i=0; i<c; i++) {
        for (j=0; j<r; j++) {
            if (map[j][i]=='*') cid[j][i] = gid;
            else if (j>0 && map[j-1][i]=='*') gid++;
        }
        if (map[r-1][i]=='*') gid++;
    }
    // printf("gid is %d\n", gid);
    memset(smap, 0, sizeof(smap));
    for (i=0; i<=gid; i++) neic[i] = 0;
    for (i=1; i<rg; i++) {
        smap[0][i] = 1;
        nei[0][neic[0]++] = i;
        nei[i][neic[i]++] = 0;
    }
    for (;i<gid; i++) {
        smap[i][gid] = 1;
        nei[i][neic[i]++] = gid;
        nei[gid][neic[gid]++] = i;
    }
    for (i=0; i<r; i++) for (j=0; j<c; j++) {
        if (map[i][j]=='.') continue;
        g1 = rid[i][j];
        g2 = cid[i][j];
        if (smap[g1][g2] == 0) {
            nei[g1][neic[g1]++] = g2;
            nei[g2][neic[g2]++] = g1;
            smap[g1][g2] = 1;
        }
    }
    // for (i=0; i<=gid; i++) {
    //     for (j=0; j<=gid; j++) printf("%d ", smap[i][j]); printf("\n");
    // }
    i = maxflow(gid);
    printf("%d\n", i);
    return 0;
}
