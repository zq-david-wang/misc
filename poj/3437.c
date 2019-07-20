#include<stdio.h>

char buf[20008];
typedef struct _T {
    struct _T *c, *n;
}TNode;
TNode pool[10004];
int pc;
TNode* build(int s, int *pi) {
    TNode *p = &pool[pc++]; p->c=NULL; p->n=NULL;
    // printf("build node from %d\n", s);
    TNode *cp = NULL, *tp;
    int i; for (i=s;;i++) {
        if (buf[i]==0) break;
        if (buf[i]=='d') {
            tp = build(i+1, &i);
            if (cp==NULL) { p->c=tp; cp=tp; }
            else { cp->n=tp; cp=tp; }
        }
        else if (buf[i]=='u') { *pi=i; break;}
    } 
    return p;
}
int height1(TNode *r) {
    if (r==NULL) return 0;
    int h=0, h1;
    TNode *p = r->c;
    while(p != NULL) {
        h1 = height1(p);
        if (h<h1) h=h1;
        p = p->n;
    }
    return h+1;
}

int height2(TNode *r) {
    if (r==NULL) return 0;
    int h=1, c=0, h1;
    TNode *p = r->c;
    while(p != NULL) {
        c++;
        h1 = height2(p)+c;
        if (h<h1) h=h1;
        p = p->n;
    }
    return h;
}
int main() {
    int i, ic=0;
    TNode *r;
    while(1) {
        scanf("%s", buf); if (buf[0]=='#') break; ic++;
        pc=0; r = build(0, &i);
        printf("Tree %d: %d => %d\n", ic, height1(r)-1, height2(r)-1);
    }
    return 0;
}
