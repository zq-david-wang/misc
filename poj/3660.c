#include<stdio.h>

typedef struct _T{
    struct _T *n;
    int b;
}WNode;
WNode pool[4500*2];
WNode *wins[101];
WNode *lose[101];
int lc[101], wc[101];
int dp1[101], dp2[101];
char flag[101];
int dfs1(int s) {
    // if (dp1[s] != -1) return dp1[s];
    WNode *p = wins[s];
    int c = 0;
    while(p!=NULL) {
        if (flag[p->b]==0) {
            flag[p->b] = 1; c++;
            c += dfs1(p->b);
        }
        p = p->n;
    }
    dp1[s] = c;
    // printf("%d wins count %d\n", s, c);
    return c;
}
int dfs2(int s) {
    // if (dp2[s] != -1) return dp2[s];
    WNode *p = lose[s];
    int c = 0;
    while(p!=NULL) {
        if (flag[p->b]==0) {
            flag[p->b] = 1; c++;
            c += dfs2(p->b);
        }
        p = p->n;
    }
    dp2[s] = c;
    // printf("%d lose count %d\n", s, c);
    return c;
}
int main() {
    int n, m, i, j, a, b;
    int pc=0;
    WNode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) { 
        wins[i] = NULL;
        lose[i] = NULL;
        dp1[i] = -1;
        dp2[i] = -1;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        p = &pool[pc++]; p->b = b; p->n = wins[a]; wins[a] = p;
        p = &pool[pc++]; p->b = a; p->n = lose[b]; lose[b] = p;
    }
    int c = 0, c1, c2;
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) flag[j] = 0;
        c1 = dfs1(i);
        for (j=1; j<=n; j++) flag[j] = 0;
        c2 = dfs2(i);
        if (c1+c2+1==n) c++;
    }
    printf("%d\n", c);
    return 0;
}
