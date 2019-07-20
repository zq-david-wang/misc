#include<stdio.h>

typedef struct _T {
    struct _T* n;
    int b;
}ENode;
ENode gpool[20000];
ENode *nei[10001];
int rc;
char flag[10001];
int dfs(int s) {
    ENode *p = nei[s];
    int r;
    int c0=0, c1=0, c2=0;
    while(p!=NULL) {
        if (flag[p->b]==0) {
            flag[p->b] = 1;
            r = dfs(p->b);
            if (r==0) c0++;
            else if (r==1) c1++;
            else c2++;
        }
        p = p->n;
    }
    if (c0>0) { rc++; return 1; }
    if (c1>0) return 2;
    return 0;
}
int main() {
    int n, i;
    int a, b;
    int gpc=0;
    ENode *p;
    scanf("%d", &n);
    for (i=1; i<=n; i++) { nei[i] = NULL; flag[i]=0; }
    for (i=0; i<n-1; i++) {
        scanf("%d %d", &a, &b);
        p = &gpool[gpc++]; p->b=b; p->n=nei[a]; nei[a] = p;
        p = &gpool[gpc++]; p->b=a; p->n=nei[b]; nei[b] = p;
    }
    rc = 0;
    flag[1] = 1;
    i = dfs(1);
    if (i==0) rc++;
    printf("%d\n", rc);
    return 0;
}
