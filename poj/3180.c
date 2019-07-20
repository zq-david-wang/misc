#include<stdio.h>

int neic[10001];
typedef struct _T{
    struct _T *n;
    short b, i;
}NNode;
NNode gpool[50000];
NNode *nei[10001];
char eflag[50000];
typedef struct {
    int low, s;
}FNode;
FNode farms[10001];

int level;
int gcc;
void dfs(int s) {
    farms[s].s = 1;
    level++;
    farms[s].low = level;
    int cl = level;
    NNode *p = nei[s];
    int b, cc=0;
    while(p!=NULL) {
        if (eflag[p->i]==0) {
            b = p->b;
            eflag[p->i]=1;
            if (farms[b].s==0) {
                b = p->b;
                dfs(b);
            }
            if (farms[s].low>farms[b].low) farms[s].low = farms[b].low;
            if (farms[b].s != 2) cc++;
        }
        p = p->n;
    } 
    if (cl==farms[s].low) {
        // printf("connect %d, count %d\n", s, cc+1);
        farms[s].s = 2;
        if (cc>0) gcc++;
    }
}
int main() {
    int f, r, i;
    int a, b;
    int gpc=0;
    level = 0;
    gcc = 0;
    NNode *p;
    scanf("%d %d", &f, &r);
    for (i=1; i<=f; i++) {
        nei[i] = NULL;
        farms[i].s = 0;
    }
    for (i=0; i<r; i++) {
        eflag[i] = 0;
        scanf("%d %d", &a, &b);
        p = &gpool[gpc++]; p->b = b; p->i = i; p->n = nei[a]; nei[a] = p;
    }
    for (i=1; i<=f; i++) {
        if (farms[i].s==0) dfs(i);
    }
    printf("%d\n", gcc);
    return 0;
}
