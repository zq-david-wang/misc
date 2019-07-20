#include<stdio.h>
#include<string.h>

typedef struct _T{
    struct _T *n;
    int b;
}ENode;
ENode gpool[20000];
int gec;
ENode *nei[1001];
ENode *rnei[1001];
char flag[1001];
void dfs(int s) {
    ENode *p = nei[s];
    while(p!=NULL) {
        if (flag[p->b]==0) {
            flag[p->b] = 1;
            dfs(p->b);
        }
        p = p->n;
    }
}
void rdfs(int s) {
    ENode *p = rnei[s];
    while(p!=NULL) {
        if (flag[p->b]==0) {
            flag[p->b] = 1;
            rdfs(p->b);
        }
        p = p->n;
    }
}
int main() {
    int n, m, i, a, b, j;
    ENode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) rnei[i] = nei[i] = NULL;
    gec = 0;
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        p = &gpool[gec++]; p->b = b; p->n = nei[a]; nei[a] = p; 
        p = &gpool[gec++]; p->b = a; p->n = rnei[b]; rnei[b] = p; 
    }
    int c = 0;
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) flag[j] = 0;
        flag[i] = 1;
        dfs(i); rdfs(i);
        for (j=i+1; j<=n; j++) if (flag[j]==0) c++;
    }
    printf("%d\n", c);
    return 0;
}
