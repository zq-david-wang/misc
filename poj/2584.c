#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char ind[128];
int map[32][32];
int flow[32][32];
int path[32];
char flag[32];
int dfs(int s, int e) {
    if (s==e) return 1;
    int i; for (i=0; i<=e; i++) {
        if (flag[i]) continue;
        if (flow[i][s]||map[s][i]>flow[s][i]) {
            flag[i]=1;
            path[i]=s;
            if (dfs(i, e)) return 1;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    memset(flag, 0, sizeof(flag));
    flag[s]=1;
    return dfs(s, e);
}
int maxflow(int s, int e) {
    memset(flow, 0, sizeof(flow));
    int r=0, f, a, b;
    while(1) {
        f=findpath(s, e);
        if (f==0) break;
        r += f;
        b=e; while(b!=s) {
            a=path[b];
            if (flow[b][a]) flow[b][a]--;
            else flow[a][b]++;
            b=a;
        }
    }
    return r;
}
int main() {
    int i, x, s, e;
    char b[16];
    ind['S']=1;
    ind['M']=2;
    ind['L']=3;
    ind['X']=4;
    ind['T']=5;
    while(1) {
        scanf("%s", b); if (b[0]=='E') break;
        memset(map, 0, sizeof(map));
        scanf("%d", &x);
        for (i=0; i<x; i++) {
            scanf("%s", b);
            s=ind[b[0]]; e=ind[b[1]];
            for (; s<=e; s++) {
                map[s][i+6]=1;
            }
            map[i+6][x+6]=1;
        }
        for (i=1; i<=5; i++) {
            scanf("%d", &s); map[0][i]=s;
        }
        i = maxflow(0, x+6);
        if (i==x) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
        scanf("%s", b);
    }
    return 0;
}


