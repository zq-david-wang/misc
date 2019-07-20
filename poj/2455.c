#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {int s, e, d;} Pipe;
Pipe pipes[40000];
int cap[204][204];
int nei[204][204];
int flow[204][204];
int neic[204];

int path[204];
char flag[204];

int mycmp(const void*a, const void*b) {
    return ((const Pipe*)a)->d - ((const Pipe*)b)->d;
}

int dfs(int s, int e, int w) {
    if (s==e) return w;
    int b, nw;
    int i; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[s][b]< cap[s][b]) {
            nw = w;
            path[b] = s;
            flag[b] = 1;
            if (nw==0 || nw>cap[s][b]-flow[s][b]) nw=cap[s][b]-flow[s][b];
            nw = dfs(b, e, nw);
            if (nw) return nw;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    memset(flag, 0, sizeof(flag));
    flag[s] = 1;
    return dfs(s, e, 0);
}
int maxflow(int s, int e) {
    int f, m=0;
    int a, b;
    memset(flow, 0, sizeof(flow));
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        m += f;
        b = e;
        while(b != s) {
            a = path[b];
            flow[a][b] += f;
            if (flow[a][b]+flow[b][a] > cap[a][b]) {
                flow[b][a] = cap[a][b]-flow[a][b];
            }
            b = a;
        }
    }
    return m;
}

int poss(int e, int t, int n) {
    memset(cap, 0, sizeof(cap));
    int i, j; for (i=0; i<=e; i++) {
        cap[pipes[i].s][pipes[i].e]++;
        cap[pipes[i].e][pipes[i].s]++;
    }
    cap[0][1] = t; cap[1][0] = t;
    cap[n][n+1] = t; cap[n+1][n] = t;
    for (i=0; i<=n+1; i++) neic[i] = 0; 
    for (i=1; i<=n; i++) {
        neic[i] = 0;
        for (j=0; j<=n+1; j++) {
            if (i==j) continue;
            if (cap[i][j]==0) continue;
            nei[i][neic[i]++] = j;
        }
    }
    neic[0] = 1; nei[0][0] = 1;
    neic[n] = 1; nei[n][0] = n+1;
    n = maxflow(0, n+1);
    // printf("maxflow for %d is %d\n", e, n);
    return n >= t;
}
int main() {
    int n, p, t, i;
    int l, h, m;
    scanf("%d %d %d", &n, &p, &t);
    for (i=0; i<p; i++) {
        scanf("%d %d %d", &pipes[i].s, &pipes[i].e, &pipes[i].d);
    }
    qsort(pipes, p, sizeof(pipes[0]), mycmp);
    l = 0; h = p-1;
    while(l<=h) {
        m = (l+h)/2;
        if (poss(m, t, n))h = m-1;
        else l = m+1;
    }
    while (l<p && !poss(l, t, n)) l++;
    printf("%d\n", pipes[l].d);
    return 0;
}
