#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char city[30][32];
int nn;
int findn(const char *n) {
    int i; for (i=0; i<nn; i++) if (strcmp(n, city[i])==0) return i;
    return -1;
}
short map[32][32];
int tas[4], tbs[4];
int gm;
struct { int cs[2]; } npool[1000000];
int gnc;
void init() {
    gnc=1;
    npool[0].cs[0]=-1;
    npool[0].cs[1]=-1;
}
int getvalue(int s) {
    int r=0, c;
    int i; for (i=0; i<nn; i++) {
        c=s&1; s>>=1;
        if (npool[r].cs[c]==-1) return -1;
        r=npool[r].cs[c];
    }
    return npool[r].cs[0];
}
void addvalue(int s, int v) {
    int r=0, c;
    printf("set state %x to %d (%d)\n", s, v, gnc);
    int i; for (i=0; i<nn; i++) {
        c=s&1; s>>=1;
        if (npool[r].cs[c]==-1) { npool[gnc].cs[0]=-1; npool[gnc].cs[1]=-1; npool[r].cs[c]=gnc++; }
        r=npool[r].cs[c];
    }
    npool[r].cs[0]=v;
}

int dfs(int s) {
    if ((s&gm)==gm) return 0;
    int a, b, r;
    r = getvalue(s); if (r!=-1) return r;
    r = 0x7fffffff;
    int i, j, t; for (i=0; i<4; i++) {
        a=tas[i]; b=tbs[i];
        if ((s&(1<<a)) || (s&(1<<b))) continue;
        for (j=0; j<nn; j++) if (map[a][j]) {
            t = dfs(s|(1<<a)|(1<<j))+map[a][j];
            if (r>t) r=t;
        }
        addvalue(s, r);
        return r;
    }
    for (i=0; i<nn; i++) {
        if (s&(1<<i)) for (j=0; j<nn; j++) {
            if (map[i][j]==0) continue;
            if (s&(1<<j)) continue;
            t = dfs(s|(1<<j))+map[i][j];
            if (r>t) r=t;
        }
    }
    addvalue(s, r);
    return r;
}
int main() {
    int n, m, i, c, s, e, a, b;
    char na[32], nb[32];
    while(1) {
        scanf("%d %d", &n, &m); if (n==0&&m==0) break;
        nn = n;
        memset(map, 0, sizeof(map));
        for (i=0; i<n; i++) scanf("%s", city[i]);
        for (i=0; i<m; i++) {
            scanf("%s %s %d", na, nb, &c);
            a = findn(na); b = findn(nb);
            if (map[a][b]==0||map[a][b]<c) {
                map[a][b]=map[b][a]=c;
            }
        }
        gm=0; for (i=0; i<4; i++) {
            scanf("%s %s", na, nb);
            a = findn(na); b = findn(nb);
            tas[i]=a; tbs[i]=b;
            gm |= (1<<a);
            gm |= (1<<b);
        }
        init();
        i=dfs(0);
        printf("%d\n", i);
    }
    return 0;
}


