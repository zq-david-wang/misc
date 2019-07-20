#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int map[24][24];
int flow[24][24];
char mark[24], flag[24];
char queue[32];
char path[32];
#define INF 0x7fffff
int dfs(int s, int e) {
    if (s==e) return 1;
    int i; for (i=0; i<=e; i++) {
        if (flag[i]) continue;
        if (map[s][i]>flow[s][i]||flow[i][s]>0) {
            flag[i]=1;
            path[i]=s;
            if (dfs(i, e)) return 1;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    int i; for (i=0; i<=e; i++) flag[i]=0;
    flag[s]=1;
    return dfs(s, e);
}
int maxflow(int s, int e) {
    memset(flow, 0, sizeof(flow));
    int r=0, f, a, b;
    while(1) {
       f = findpath(s, e); 
       if (f==0) break;
       r++;
       b = e;
       while(b!=s) {
           a = path[b];
           if (flow[b][a]) flow[b][a]--;
           else flow[a][b]++;
           b = a;
       }
    }
    return r;
}
int main() {
    int ti, tc, m, n, i, c, j, k;
    char ss[8], head, tail;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &m, &n);
        for (i=0; i<m; i++) flag[i]=mark[i]=0;
        memset(map, 0, sizeof(map));
        head=tail=0;
        for (i=0; i<m; i++) {
            scanf("%s %d", ss, &c);
            if (ss[0]=='I') { queue[head++] = i; flag[i]=1;}
            for (j=0; j<c; j++) {
                scanf("%d", &k);
                map[i][k]++;
            }
        }
        while(tail<head) {
            i = queue[tail++];
            for (j=0; j<m; j++) {
                if (map[i][j]==0) continue;
                if (flag[j]) continue;
                flag[j]=1;
                queue[head++] = j;
            }
        }
        if (flag[n]) { printf("PANIC ROOM BREACH\n"); continue; }
        // maxflow m+1->m;
        for (i=0; i<m; i++) {
            if (flag[i]==0) continue;
            map[i][m] = INF;
        }
        mark[n]=1;
        head=tail=0; queue[head++] = n;
        while(tail<head) {
            i=queue[tail++];
            for (j=0; j<m; j++) {
                if (map[j][i]==0) continue;
                if (mark[j]) continue;
                mark[j]=1;
                queue[head++] = j;
            }
        }
        for (i=0; i<m; i++) {
            if (mark[i]==0) continue;
            map[m+1][i]=INF;
        }
        i = maxflow(m+1, m);
        printf("%d\n", i);
    }
    return 0;
}


