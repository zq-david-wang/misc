#include<stdio.h>
#include<string.h>

int fmap[1004][1004];
int flow[1004][1004];
int nei[1004][1004];
int neic[1004];
int path[1004];
char flag[1004];

char dfs(int s, int n) {
    if (s==n) return 1;
    int i, b; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[b][s]==0 && flow[s][b]==fmap[s][b]) continue;
        flag[b] = 1;
        path[b] = s;
        if (dfs(b, n)) return 1;
    }
    return 0;
}
char findpath(int n) {
    memset(flag, 0, n+1);
    flag[0] = 1;
    return dfs(0, n);
}
int maxflow(int n) {
    int r = 0, f, b, a;
    while(1) {
        f = findpath(n+n+1);
        if (f==0) break;
        r++;
        b = n+n+1;
        while(b != 0) {
            a = path[b];
            if (flow[a][b]<fmap[a][b]) flow[a][b] += 1;
            else flow[b][a] -= 1;
            b = a;
        }
    }
    return r;
}
int main() {
    int n, k, i, j;
    int a, b;
    scanf("%d %d", &n, &k);
    memset(fmap, 0, sizeof(fmap));
    memset(flow, 0, sizeof(flow));
    memset(neic, 0, sizeof(neic));
    for (i=1; i<=n; i++) {
        fmap[0][i] = 1;
        nei[0][neic[0]++] = i;
        nei[i][neic[i]++] = 0;
        fmap[i+n][n+n+1] = 1;
        nei[i+n][neic[i+n]++] = n+n+1;
        nei[n+n+1][neic[n+n+1]++] = i+n;
    }
    for (i=0; i<k; i++) {
        // 
        scanf("%d %d", &a, &b);
        if (fmap[a][b+n]==0) {
            nei[a][neic[a]++] = b+n;
            nei[b+n][neic[b+n]++] = a;
        }
        fmap[a][b+n]++;
    }
    // for (i=0; i<=n+n+1; i++) { for (j=0; j<=n+n+1; j++) printf("%d ", fmap[i][j]); printf("\n"); }
    // for (i=0; i<=n+n+1; i++) { printf("%d:", i); for (j=0; j<neic[i]; j++) printf(" %d", nei[i][j]); printf("\n"); }
    i = maxflow(n);
    printf("%d\n", i);
    return 0;
}
