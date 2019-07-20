#include<stdio.h>
#include<string.h>

int rank[1001][20];
short flow[1024][1024];
short map[1024][1024];
short nei[1024][1024];
short neic[1024];
int path[1024];
char flag[1024];
int cap[20];
int buck[20];


int dfs(int s, int n) {
    if (s==n) return 1;
    int b, i; 
    for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[s][b]<map[s][b] || flow[b][s]>0) {
            flag[b] = 1;
            path[b] = s;
            if (dfs(b, n)) return 1;
        }
    }
    return 0;
}
int findpath(int n) {
    memset(flag, 0, sizeof(flag));
    flag[0] = 1;
    return dfs(0, n);
}
int maxflow(int n) {
    int r = 0, f, a, b;
    while(1) {
        f = findpath(n);
        if (f==0) break;
        r += f;
        b = n;
        while(b!=0) {
            a = path[b];
            if (flow[b][a]) flow[b][a] -= 1;
            else flow[a][b] += 1;
            b = a;
        } 
    }
    return r;
}
int main() {
    int n, b, i, j, f, r=-2, t, k;
    scanf("%d %d", &n, &b);
    for (i=1; i<=n; i++) {
        for (j=0; j<b; j++) scanf("%d", &rank[i][j]);
    }
    for (i=0; i<b; i++) scanf("%d", &cap[i]);
    for (i=0; i<=n+b+1; i++) neic[i] = 0;
    memset(map, 0, sizeof(map));
    for (i=1; i<=n; i++) {
        map[0][i] = 1;
        nei[0][neic[0]++] = i;
        nei[i][0] = 0;
        neic[i] = 1;
    }
    for (i=n+1; i<=n+b; i++) {
        map[i][n+b+1] = cap[i-n-1];
        nei[i][0] = n+b+1;
        neic[i] = 1;
        nei[b+n+1][neic[n+b+1]++] = i;
    }
    for (i=1; i<=n; i++) for (j=0; j<b; j++) {
        t = rank[i][j];
        map[i][t+n] = 1;
    }
    /* 
    for (i=0; i<b; i++) buck[i] = 0;
    for (i=1; i<=n; i++) buck[rank[i][0]-1]++; 
    for (i=0; i<b; i++) printf("%d: %d,%d\n", i, buck[i], cap[i]);
    */
    // int ii, jj;
    for (i=0; i<b; i++) {
        for (k=1; k<=n; k++) neic[k] = 1;
        for (k=1; k<=b; k++) neic[n+k] = 1;
        /* 
        for (ii=1; ii<=n; ii++) for (jj=0; jj<b; jj++) {
            t = rank[ii][jj];
            map[ii][t+n] = 0;
        }
        */
        for (j=0; j+i<b; j++) {
            // build map 
            for (k=1; k<=n; k++) {
                t = rank[k][j+i];
                nei[k][neic[k]++] = n+t;
                nei[n+t][neic[n+t]++] = k;
                // map[k][t+n] = 1;
            }
            memset(flow, 0, sizeof(flow));
            f = maxflow(n+b+1);
            if (f==n) break;
        }
        if (j+i<b) {
            if (r<0 || r>j) {
                r=j;
                // printf("update %d, len %d\n", i, j);
            }
        } else break;
    }
    r++;
    printf("%d\n", r);
    return 0;
}
