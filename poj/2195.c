#include<stdio.h>
#include<string.h>

char line[128];
typedef struct { char r, c; }LNode;
LNode homes[128], minions[128];
int hc, mc;

char map[208][208];
char flow[208][208];
short neic[208];
short nei[208][208];
short path[208];
char flag[208];
int costs[208][208], gcost;
#define INF 0x7fffffff
int dist[208];
#define MOD 256
int queue[MOD+4];
char findpath(int s, int e) {
    int i; for (i=s; i<=e; i++) { flag[i]=0; dist[i]=INF; }
    flag[s]=1; dist[s]=0;
    int head=0, tail=0, a, b;
    queue[head++] = s;
    while(tail != head) {
        a = queue[tail++]; tail %=MOD;
        flag[a]=0;
        for (i=0; i<neic[a]; i++) {
            b = nei[a][i];
            if ((map[a][b]-flow[a][b]==0)&&flow[b][a]==0) continue;
            if (dist[a]+costs[a][b]<dist[b]) {
                dist[b]=dist[a]+costs[a][b];
                path[b]=a;
                if (flag[b]==0) {
                    queue[head++] = b; head %= MOD;
                    flag[b]=1;
                }
            }
        }
    }
    if (dist[e]==INF) return 0;
    gcost += dist[e];
    return 1;
}
int maxflow(int s, int e) {
    int r=0, f, a, b;
    while(1) {
        f=findpath(s, e);
        if (f==0) break;
        r+=f;
        b=e;
        while(b!=s) {
            a=path[b];
            if (flow[b][a]) { 
                flow[b][a]=0;
            } else { 
                flow[a][b]=1;
            }
            costs[b][a] -= costs[a][b];
            costs[a][b] = 0;
            b=a;
        }
    }
    // printf("maxflow %d->%d %d\n", s, e, r);
    return r;
}
void check() {
    memset(map, 0, sizeof(map));
    memset(flow, 0, sizeof(flow));
    memset(costs, 0, sizeof(costs));
    int s=0, e=hc+mc+1;
    int i, j, dr, dc; for (i=0; i<=e; i++) neic[i]=0;
    for (i=1; i<=mc; i++) {
        map[s][i]=1;
        nei[s][neic[s]++] = i;
        nei[i][neic[i]++] = s;
    }
    for (i=mc+1; i<=mc+hc; i++) {
        map[i][e] = 1;
        nei[e][neic[e]++] = i;
        nei[i][neic[i]++] = e;
    }
    for (i=0; i<mc; i++) {
        for (j=0; j<hc; j++) {
            dr=homes[j].r-minions[i].r; if (dr<0) dr=-dr;
            dc=homes[j].c-minions[i].c; if (dc<0) dc=-dc;
            s = i+1; e=mc+1+j;
            map[s][e] = 1;
            nei[s][neic[s]++] = e;
            nei[e][neic[e]++] = s;
            costs[s][e] = dr+dc;
        }
    }
    maxflow(0, mc+hc+1);
}
int main() {
    int n, m, i, j;
    while(1) {
        scanf("%d %d", &n, &m); if(n==0) break;
        hc=0; mc=0;
        for (i=0; i<n; i++) {
            scanf("%s", line);
            j=0; while(line[j]) {
                if (line[j]=='m') { minions[mc].r=i; minions[mc].c=j; mc++; }
                if (line[j]=='H') { homes[hc].r=i; homes[hc].c=j; hc++; }
                j++;
            }
        }
        gcost=0;
        check();    
        printf("%d\n", gcost);
    }
    return 0;
}
