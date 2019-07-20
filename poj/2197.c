#include<stdio.h>

int dis[32][32], gcc, gn;
char map[32][32], flag[32], path[32];
void dfs(int s, int c, int e, int cd, int d) {
    if (s==e) {
        if (cd!=d) return;
        printf(" %d:", d);
        for (s=0; s<c; s++) printf(" %d", path[s]); printf(" \n");
        gcc++;
        return;
    }
    if (cd>d) return;
    int i; for (i=1; i<=gn; i++) {
        if (flag[i]) continue;
        if (map[s][i]==0) continue;
        flag[i]=1;
        path[c]=i;
        dfs(i, c+1, e, cd+dis[s][i], d);
        flag[i]=0;
    }
}
int main() {
    int v, r, i, j, ci=0;
    int a, b, d, s, e, m;
    while(1) {
        scanf("%d", &v); if (v==-1) break; ci++;
        for (i=1; i<=v; i++) flag[i]=0;
        for (i=1; i<=v; i++) for (j=1; j<=v; j++) map[i][j]=0;
        scanf("%d", &r);
        for (i=0; i<r; i++) {
            scanf("%d %d %d", &a, &b, &d);
            map[a][b]=1; dis[a][b]=d;
            map[b][a]=1; dis[b][a]=d;
        }
        scanf("%d %d %d", &s, &e, &m);
        if (ci>1) printf("\n");
        printf("Case %d:\n", ci);
        gcc = 0; path[0]=s; gn=v; flag[s]=1;
        for (d=1; d<=m; d++) {
            dfs(s, 1, e, 0, d);
        }
        if (gcc==0) printf(" NO ACCEPTABLE TOURS\n");
    }
    return 0;
}
