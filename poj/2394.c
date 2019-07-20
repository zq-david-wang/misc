#include<stdio.h>

int map[501][501];
int cowi[101];
int spath[501];
char flag[501];
#define INF -1
int main() {
    int f, p, c, m, i, j;
    int a, b, d, cc;
    scanf("%d %d %d %d", &f, &p, &c, &m);
    for (i=1; i<=f; i++) for (j=1; j<=f; j++) map[i][j] = INF;
    for (i=0; i<p; i++) {
        scanf("%d %d %d", &a, &b, &d);
        if (map[a][b]==-1 || map[a][b]>d) {
            map[a][b] = d;
            map[b][a] = d;
        }
    }
    for (i=1; i<=c; i++) scanf("%d", &cowi[i]);
    for (i=1; i<=f; i++) { 
        spath[i] = INF;
        flag[i] = 0;
    }
    spath[1] = 0;
    while(1) {
        d = INF;
        for (i=1; i<=f; i++) {
            if (flag[i]) continue;
            if (spath[i]==INF) continue;
            if (d==INF || d>spath[i]) {
                d = spath[i];
                a = i;
            }
        }
        if (d==INF) break;
        flag[a] = 1;
        for (i=1; i<=f; i++) {
            if (flag[i]) continue;
            if (map[a][i]==INF) continue;
            if (spath[i]==INF || map[a][i]+d < spath[i]) spath[i] = map[a][i]+d;
        }
    }
    cc = 0;
    for (i=1; i<=c; i++) {
        a = cowi[i];
        if (spath[a]==INF) continue;
        if (spath[a]<=m) cowi[cc++] = i;
    }
    printf("%d\n", cc);
    for (i=0; i<cc; i++) printf("%d\n", cowi[i]);
    return 0;
}
