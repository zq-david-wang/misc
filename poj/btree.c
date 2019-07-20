#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int KEY;
typedef int VALUE;
#define kcmp(x, y) (x-y)

typedef struct _T {
    struct _T *l, *r, *p;
    KEY k;
    VALUE v;
    int c;
}TNode;

typedef struct {
    TNode *root;
}BTree;


#define MAXPC 10000
TNode* gpool;
int gpc=0;
TNode *freelist;
BTree gtree = { NULL };
void init() {
    freelist = NULL;
    gpc=0; gpool = (TNode *)malloc(MAXPC*sizeof(TNode));
    gtree.root = NULL;
}
TNode *alloc(KEY k) {
    TNode *r;
    if (freelist) {
        r = freelist;
        freelist = freelist->r;
    } else {
        if (gpc==MAXPC) {
            gpc=0; gpool = (TNode *)malloc(MAXPC*sizeof(TNode));
        }
        r = &gpool[gpc++];
    }
    r->l = r->r = r->p = NULL;
    r->k = k;
    r->c = 1;
    return r;
}
void release(TNode *p) {
    p->r = freelist;
    freelist = p;
}

TNode *search(BTree *tree, KEY v) {
    TNode *r = tree->root;
    int c;
    while(r!=NULL) {
        c = kcmp(r->k, v);
        if (c==0) break;
        if (c>0) r = r->l;
        else r = r->r;
    }
    return r;
}

TNode *minimum(TNode *r) {
    while(r!=NULL&&r->l!=NULL) r=r->l;
    return r;
}

TNode *maximum(TNode *r) {
    while(r!=NULL&&r->r!=NULL) r=r->r;
    return r;
}

TNode *successor(TNode *r) {
    if (r->r) return minimum(r->r);
    TNode *p = r->p;
    while(p!=NULL && r==p->r) {
        r = p; p = r->p;
    }
    return p;
}

TNode *predecessor(TNode *r) {
    if (r->l) return maximum(r->l);
    TNode *p = r->p;
    while(p!=NULL && r==p->l) {
        r = p; p=r->p;
    }
    return p;
}

void insert(BTree *tree, KEY k, VALUE v) {
    TNode *p = NULL, *np, *r = tree->root;
    int c;
    while(r!=NULL) {
        p = r;
        c = kcmp(r->k, k);
        if (c==0) {
            r->c++;
            return;
        } else if (c>0) r = r->l;
        else r = r->r;
    }
    np = alloc(k);
    np->v = v;  np->p = p;
    if (p==NULL) {
        tree->root = np;
    } else if (c>0) p->l = np;
    else p->r = np;
    return;
}

void *transplant(BTree *tree, TNode *a, TNode *b) {
    if (a->p == NULL) { tree->root = b; }
    else if (a->p->l == a) a->p->l = b;
    else a->p->r = b;
    if (b != NULL) b->p = a->p;
}

void delete(BTree *tree, TNode *a) {
    a->c--; if (a->c) return;
    if (a->l==NULL) transplant(tree, a, a->r);
    else if (a->r==NULL) transplant(tree, a, a->l);
    else {
        TNode *p = minimum(a->r);
        if (p->p != a) {
            transplant(tree, p, p->r);
            p->r = a->r;
            p->r->p = p;
        }
        transplant(tree, a, p);
        p->l = a->l;
        p->l->p = p;
    }
    release(a);
}
void inorder(TNode *r) {
    if (r==NULL) return ;
    inorder(r->l);
    printf("(%d,%d) ", r->k, r->v);
    inorder(r->r);
}

int main() {
    init(); 
    int i;
    for (i=1000; i>=0; i--) {
        insert(&gtree, i, i*i);
    }
    for (i=1000; i>=0; i--) {
        delete(&gtree, search(&gtree, i));
    }
    for (i=1000; i>=0; i--) {
        insert(&gtree, i, i*i);
    }
    for (i=999; i>=0; i--) {
        delete(&gtree, search(&gtree, i));
    }
    inorder(gtree.root);
    return 0;
}


