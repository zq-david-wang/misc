#include<stdio.h>
#include<string.h>

int fs[101], ds[101];
char map[402][402];
char flow[402][402];
int nei[402][402];
int neic[402];
char flag[402];
int path[402];

int dfs(int s, int e) {
    if (s==e) return 1;
    int a=s, b, i;
    for (i=0; i<neic[a]; i++) {
        b = nei[a][i];
        if (flag[b]) continue;
        if (flow[b][a]==1 || (flow[a][b]==0&&map[a][b]==1)) {
            path[b] = a;
            flag[b] = 1;
            if (dfs(b, e)) return 1;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    int i; for (i=s; i<=e; i++) flag[i] = 0;
    flag[s] = 1;
    return dfs(s, e);
}
int maxflow(int s, int e) {
    int mf = 0, f, a, b;
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        mf += f;
        b = e;
        while(b != s) {
            a = path[b];
            if (flow[b][a]) flow[b][a] = 0;
            else flow[a][b] = 1;
            b = a;
        }
    }
    return mf;
}
int main() {
    int n, f, d, i, j, k;
    int a, b;
    int fc, dc;
    scanf("%d %d %d", &n, &f, &d);
    memset(map, 0, sizeof(map));
    memset(flow, 0, sizeof(flow));
    memset(neic, 0, sizeof(neic));
    a = 0;
    for (i=1; i<=f; i++) {
        b = i;
        map[a][b] = 1;
        nei[a][neic[a]++] = b;
        nei[b][neic[b]++] = a;
    }
    b = n+n+f+d+1;
    for (i=1; i<=d; i++) {
        a = n+n+f+i;
        map[a][b] = 1;
        nei[a][neic[a]++] = b;
        nei[b][neic[b]++] = a;
    }
    for (i=1; i<=n; i++) {
        a = f+i;
        b = f+i+n;
        map[a][b] = 1;
        nei[a][neic[a]++] = b;
        nei[b][neic[b]++] = a;
    }
    int v;
    for (i=1; i<=n; i++) {
        scanf("%d %d", &fc, &dc);
        b = f+i; for (j=0; j<fc; j++) {
            scanf("%d", &v);
            a = v;
            map[a][b] = 1;
            nei[a][neic[a]++] = b;
            nei[b][neic[b]++] = a;
        }
        a = n+f+i; for (j=0; j<dc; j++) {
            scanf("%d", &v);
            b = v+f+n+n;
            map[a][b] = 1;
            nei[a][neic[a]++] = b;
            nei[b][neic[b]++] = a;
        }
    }
    // for (i=0; i<=n+f+d+1; i++) { for (j=0; j<=n+f+d+1; j++) printf("%d ", map[i][j]); printf("\n"); }
    // for (i=0; i<=n+f+d+1; i++) printf("%d: %d\n", i, neic[i]);
    i = maxflow(0, f+d+n+n+1);
    printf("%d\n", i);
    return 0;
}
