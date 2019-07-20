#include<stdio.h>
#include<string.h>

unsigned char rmap[232][232];
int spath[31][232];
char flag[232];
#define INF 0x7fffffff
int fmap[232][232];
int flow[232][232];
int nei[232][232];
int neic[232];
int ppath[232];
char flag[232];
int dfs(int s, int e) {
    if (s==e) return 1;
    int i, b; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[b][s]>0 || (fmap[s][b]>flow[s][b])) {
            flag[b] = 1;
            ppath[b] = s;
            if (dfs(b, e)) return 1;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    memset(flag, 0, sizeof(flag));
    flag[s] = 1;
    return dfs(s, e);
}
int maxflow(int s, int e) {
    memset(flow, 0, sizeof(flow));
    int r = 0, f, a, b;
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        r += f;
        b = e;
        while(b != s) {
            a = ppath[b];
            if (flow[b][a]>=f) flow[b][a] -= f;
            else flow[a][b] += f;
            b = a;
        }
    }
    return r;
}
char possible(int m, int k, int c, int l) {
    // printf("try %d with %d %d %d\n", m, k, c, l);
    // make map
    memset(fmap, 0, sizeof(fmap));
    int n = k+c+1;
    int i, j; for (i=0; i<=n; i++) neic[i]=0;
    for (i=1; i<=k; i++) {
        fmap[0][i]=l;
        nei[0][neic[0]++] = i;
        nei[i][neic[i]++] = 0;
    }
    for (i=k+1; i<=k+c; i++) {
        fmap[i][n] = 1;
        nei[i][neic[i]++] = n;
        nei[n][neic[n]++] = i;
    }
    for (i=k+1; i<=k+c; i++) {
        for (j=1; j<=k; j++) {
            if (spath[j][i]>m) continue;
            fmap[j][i] = 1;
            nei[j][neic[j]++] = i;
            nei[i][neic[i]++] = j;
        }
    }
    return maxflow(0, n)==c;
}
int main() {
    int k, c, m, i, j, mi, md, d;
    int low=0, high=0, mv;
    scanf("%d %d %d", &k, &c, &m);
    for (i=1; i<=k+c; i++) {
        for (j=1; j<=k+c; j++) {
            scanf("%d", &d);
            rmap[i][j] = d;
        }
    }
    for (i=1; i<=k; i++) {
        for (j=1;j<=k+c; j++) {
            spath[i][j] = INF;
            flag[j] = 0;
        }
        spath[i][i] = 0;
        while(1) {
            md = INF;
            for (j=1; j<=k+c; j++) {
                if (flag[j]) continue;
                if (md>spath[i][j]) {
                    md = spath[i][j];
                    mi = j;
                }
            }
            if (md==INF) break;
            if (high<md) high = md;
            flag[mi] = 1;
            // printf("spath %d <-> %d ==> %d\n", i, mi, md);
            for (j=1; j<=k+c; j++) {
                if (flag[j] || rmap[mi][j]==0) continue;
                if (md+rmap[mi][j] < spath[i][j]) spath[i][j] = md+rmap[mi][j];
            }
        }
    }
    while(low<=high) {
        mv = (low+high)/2;
        if (possible(mv, k, c, m)) {
            if (high==mv) break;
            high = mv;
        } else low = mv+1;
    }
    printf("%d\n", high); 
    return 0;
}
