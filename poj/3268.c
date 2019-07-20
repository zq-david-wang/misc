#include<stdio.h>

int map[1001][1001];
int nei[1001][1001];
int neic[1001];
int rnei[1001][1001];
int rneic[1001];
int path[1001], rpath[1001];
char flag[1001];
#define INF 0x7fffffff
int main() {
    int n, m, x, i, a, b, d, j;
    scanf("%d %d %d", &n, &m, &x);
    for (i=1; i<=n; i++) {
        neic[i] = rneic[i] = 0;
        path[i] = rpath[i] = INF;
    }
    for (i=1; i<=n; i++) for (j=1; j<=n; j++) map[i][j] = INF;
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &d);
        if (map[a][b]==INF) {
            nei[a][neic[a]++] = b;
            rnei[b][rneic[b]++] = a;
        }
        if (map[a][b]>d) map[a][b] = d;
    }
    for (i=1; i<=n; i++) flag[i] = 0;
    path[x] = 0;
    int md, mi;
    while(1) {
        md = INF;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (md>path[i]) { md = path[i]; mi = i; }
        }
        if (md==INF) break;
        a = mi;
        flag[mi] = 1;
        for (i=0; i<neic[a]; i++) {
            b = nei[a][i];
            if (flag[b]) continue;
            if (md+map[a][b] < path[b]) path[b] = md+map[a][b];
        }
    }
    for (i=1; i<=n; i++) flag[i] = 0;
    rpath[x] = 0;
    while(1) {
        md = INF;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (md>rpath[i]) { md = rpath[i]; mi = i; }
        }
        if(md==INF) break;
        b = mi;
        flag[mi] = 1;
        for (i=0; i<rneic[b]; i++) {
            a = rnei[b][i];
            if (flag[a]) continue;
            if (md+map[a][b]<rpath[a])rpath[a] = md+map[a][b];
        }
    }
    md = 0;
    for (i=1; i<=n; i++) {
        d = path[i]+rpath[i];
        if (md<d) md = d;
    }
    printf("%d\n", md);
    return 0;
}
