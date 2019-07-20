#include<stdio.h>

char ef[50001];
struct { int a, b;} edges[50001];
typedef struct _T{
    struct _T* n;
    int ei;
}LNode;
LNode *ned[10001];
LNode gpool[100002];
int gpc = 0;
LNode *alloc(int i) {
    LNode *r=  &gpool[gpc++];
    r->ei = i;
    r->n = NULL;
    return r;
}
void dfs(int s) {
    LNode *p = ned[s];
    int e, b, r=1;
    printf("%d\n", s);
    while(p!=NULL) {
        e = p->ei;
        if (ef[e]==0) {
            ef[e] = 1;
            b = edges[e].a;
            if (b==s) b = edges[e].b;
            dfs(b);
            ef[e] = 2;
            r = 0;
            printf("%d\n", s);
        }
        p = p->n;
    }
}
int main() {
    int n, m, i, a, b;
    LNode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) ned[i] = NULL;
    for (i=1; i<=m; i++) {
        ef[i] = 0;
        scanf("%d %d", &a, &b);
        edges[i].a = a;
        edges[i].b = b;
        p = alloc(i); p->n = ned[a]; ned[a] = p;
        p = alloc(i); p->n = ned[b]; ned[b] = p;
    }
    dfs(1);
    return 0;
}
