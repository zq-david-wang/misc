#include<stdio.h>

typedef struct _T{
    struct _T *n;
    int b;
}ENode;
ENode pool[50000*2];
ENode *cs[10001];
ENode *rcs[10001];
char flag[10001];
char mflag[10001];
int gc, gcc;
int stack[10001];
int stop;
void dfs(int s) {
    stack[stop++] = s;
    ENode *p = cs[s];
    while(p!=NULL) {
        if (mflag[p->b]==0) {
            gc++;
            mflag[p->b] = 1;
            dfs(p->b);
        }
        p = p->n;
    }
}
void rdfs(int s) {
    ENode *p = rcs[s];
    while(p!=NULL) {
        if (flag[p->b]==0) {
            gcc++;
            flag[p->b] = 1;
            rdfs(p->b);
        }
        p = p->n;
    }
}
int main() {
    int n, m, i, pc=0;
    int a, b, j;
    ENode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) { 
        cs[i]=NULL;
        rcs[i]=NULL;
        flag[i] = 0;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        p = &pool[pc++]; p->b = a; p->n = cs[b]; cs[b] = p;
        p = &pool[pc++]; p->b = b; p->n = rcs[a]; rcs[a] = p;
    }
    gcc = 0;
    for (j=1; j<=n; j++) mflag[j]=0;
    for (i=1; i<=n; i++) {
        if (rcs[i]) continue;
        if (flag[i]) continue;
        mflag[i] = 1;
        stop = 0;
        dfs(i);
        if (stop==n) {
            gcc++;
            for (j=0; j<stop; j++) mflag[stack[j]] = 0;
            stop=0;
            flag[i] = 1;
            rdfs(i);
        }
        for (j=1; j<stop; j++) {
            flag[stack[j]] = 1;
            mflag[stack[j]] = 0;
        }
    }
    for (i=1; i<=n; i++) {
        if (flag[i]) continue;
        mflag[i] = 1;
        stop = 0;
        dfs(i);
        if (stop==n) {
            gcc++;
            for (j=0; j<stop; j++) mflag[stack[j]] = 0;
            stop=0;
            flag[i] = 1;
            rdfs(i);
        }
        for (j=0; j<stop; j++) {
            flag[stack[j]] = 1;
            mflag[stack[j]] = 0;
        }
    }
    printf("%d\n", gcc);

    return 0;
}
