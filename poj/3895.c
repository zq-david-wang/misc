#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct { short n, b; } npool[4444*4444];;
char flag[5000];
short depth[5000];
int nei[5000];
int npc, gml;
void dfs(int s, int d) {
    depth[s] =d;
    int j = nei[s];
    int b, dd;
    while(j!=-1) {
        b = npool[j].b;
        if (flag[b]) {
            dd = d-depth[b]+1;
            if (dd>=3 && gml<dd) gml=dd;
        } else {
            flag[b]=1;
            dfs(b, d+1);
        }
        j = npool[j].n;
    }
}
int main() {
    int tc, ti, n, m, i;
    int a, b;
    scanf("%d", &tc); for (ti=0;ti<tc;ti++) {
        scanf("%d %d", &n, &m);
        for (i=1; i<=n; i++) { nei[i]=-1; flag[i]=0; }
        npc=0;
        for (i=0; i<m; i++) {
            scanf("%d %d", &a, &b);
            npool[npc].n=nei[a]; npool[npc].b=b; nei[a]=npc++;
            npool[npc].n=nei[b]; npool[npc].b=a; nei[b]=npc++;
        }
        gml=0;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            flag[i]=1; dfs(i, 0);
        }
        printf("%d\n", gml);
    }
    return 0;
}


