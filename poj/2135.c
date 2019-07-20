#include<stdio.h>
#include<string.h>

char map[1000][1000];
char flow[1000][1000];
int dis[1000][1000][2];
int spath[1000], pi[1000];
char flag[1000];
#define INF 0x7fffffff
typedef struct { int b, d; }ENode;
ENode nei[1000][1000];
int neic[1000];
#define MOD 2000
int queue[MOD];
int main() {
    int n, m, i, c, j;
    int a, b, d;
    scanf("%d %d", &n, &m);
    memset(map, 0, sizeof(map));
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &d);
        a--; b--;
        c = map[a][b];
        for (j=c-1; j>=0; j--) {
            if (dis[a][b][j]<=d) break;
            if (j==0) { dis[a][b][1] = dis[a][b][0]; dis[b][a][1] = dis[b][a][0]; }
        }
        j++; if (j<2) { dis[a][b][j] = d; dis[b][a][j] = d; }
        if (map[a][b]<2) { map[a][b]++; map[b][a]++; }
    }
    memset(flow, 0, sizeof(flow));
    for (i=0; i<n; i++) { flag[i] = 0; spath[i] = INF; } 
    spath[0] = 0;
    while(1) {
        d = INF;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (d>spath[i]) {
                j = i; 
                d = spath[i];
            }
        }
        if (d==INF) break;
        if (j==n-1) break;
        flag[j] = 1;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (map[j][i]==0) continue;
            if (dis[j][i][0]+d<spath[i]) {
                spath[i] = dis[j][i][0]+d;
                pi[i] = j;
            }
        }
    }
    // mark flow
    b = n-1;
    while(b != 0) {
        a = pi[b];
        flow[a][b] = 1;
        b = a;
    }
    int r = spath[n-1];
    for (i=0; i<n; i++) neic[i] = 0;
    for (i=0; i<n; i++) for (j=i+1; j<n; j++) {
        if (map[i][j]==0) continue;
        if (flow[i][j]) {
            nei[j][neic[j]].b = i; nei[j][neic[j]].d = -dis[i][j][0]; neic[j]++;
            if (map[i][j]>1) {
                nei[i][neic[i]].b = j; nei[i][neic[i]].d = dis[i][j][1]; neic[i]++;
            }
        } else if (flow[j][i]) {
            nei[i][neic[i]].b = j; nei[i][neic[i]].d = -dis[i][j][0]; neic[i]++;
            if (map[i][j]>1) {
                nei[j][neic[j]].b = i; nei[j][neic[j]].d = dis[i][j][1]; neic[j]++;
            }
        } else {
            nei[i][neic[i]].b = j; nei[i][neic[i]].d = dis[i][j][0]; neic[i]++;
            nei[j][neic[j]].b = i; nei[j][neic[j]].d = dis[i][j][0]; neic[j]++;
        }
    }
    for (i=0; i<n; i++) { flag[i] = 0; spath[i] = INF; } 
    spath[0] = 0;
    // spfa
    int head=0, tail=0;
    queue[head++] = 0;
    flag[0] = 1;
    while(tail != head) {
        a = queue[tail++]; tail %=MOD;
        flag[a] = 0;
        for (j=0; j<neic[a]; j++) {
            b = nei[a][j].b;
            d = nei[a][j].d;
            if (spath[a]+d<spath[b]) {
                spath[b] = spath[a]+d;
                if (flag[b]==0) {
                    queue[head++] = b; head %=MOD;
                    flag[b] = 1;
                }
            }
        }
    }
    r += spath[n-1];
    printf("%d\n", r);
    return 0;
}
