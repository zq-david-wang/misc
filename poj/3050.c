#include<stdio.h>

typedef struct _T {
    struct _T *cs[10];
    int c;
}NNode;

NNode gpool[100000];
int gpc;
NNode *alloc() {
    NNode *r = &gpool[gpc++];
    int i; for (i=0; i<10; i++) r->cs[i] = NULL;
    r->c = 0;
    return r;
}
NNode *root;
int gc;
void init() {
    gpc = 0;
    root = alloc();
    gc = 0;
}

void add(char *n) {
    int i; for (i=0; i<6; i++) if (n[i]!=0) break;
    NNode *p = root;
    char c;
    for (; i<6; i++){
        c = n[i];
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    if (p->c==0) gc++;
    p->c = 1;
}

int map[8][8];
char path[8];
void dfs(int i, int j, int c) {
    path[c] = map[i][j];
    if (c==5) {
        add(path);
        return;
    }
    if (i>0) dfs(i-1, j, c+1);
    if (i<4) dfs(i+1, j, c+1);
    if (j>0) dfs(i, j-1, c+1);
    if (j<4) dfs(i, j+1, c+1);
}
int main() {
    int i, j; 
    init();
    for (i=0; i<5; i++) for (j=0; j<5; j++) scanf("%d", &map[i][j]);
    for (i=0; i<5; i++) for (j=0; j<5; j++) dfs(i, j, 0);
    printf("%d\n", gc);
    return 0;
}
