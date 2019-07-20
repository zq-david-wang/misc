#include<stdio.h>

int neic[5001];
typedef struct _T{
    struct _T *n;
    short b, i;
}NNode;
NNode gpool[20000];
NNode *nei[5001];
char eflag[10000];
typedef struct {
    int low, cc, s;
}FNode;
FNode farms[5001];

int level;
short gflag[1000];
int gcc;
void dfs(int s) {
    farms[s].s = 1;
    farms[s].cc = 0;
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
            cc += farms[b].cc;
        }
        p = p->n;
    } 
    if (cl==farms[s].low) {
        // printf("connect %d: cc %d\n", s, cc);
        gflag[gcc] = cc;
        gcc++;
        cc = 1;
    }
    farms[s].cc = cc;
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
        p = &gpool[gpc++]; p->b = a; p->i = i; p->n = nei[b]; nei[b] = p;
    }
    dfs(1);
    if (gcc==1) printf("0\n");
    else {
        a = 0;
        for (i=0; i<gcc; i++) if (gflag[i]==0)a++;
        if (gflag[gcc-1]==1) a++;
        a = (a+1)/2;
        printf("%d\n", a);
    }
    return 0;
}
