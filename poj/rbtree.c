#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int KEY;
typedef int VALUE;
#define kcmp(x, y) (x-y)
#define BLACK 1
#define RED 0

typedef struct _T {
    struct _T *l, *r, *p;
    KEY k;
    VALUE v;
    short c, color;
}TNode;

typedef struct {
    TNode *root;
}BTree;
TNode dummy, *nil;


#define MAXPC 10000
TNode* gpool;
int gpc=0;
TNode *freelist;
BTree gtree;
void init() {
    gpc=0; gpool = (TNode *)malloc(MAXPC*sizeof(TNode));
    dummy.color = BLACK;
    dummy.p = NULL;
    nil = &dummy;
    gtree.root = nil;
    freelist = nil;
}
TNode *alloc(KEY k) {
    TNode *r;
    if (freelist!=nil) {
        r = freelist;
        freelist = freelist->r;
    } else {
        if (gpc==MAXPC) {
            gpc=0; gpool = (TNode *)malloc(MAXPC*sizeof(TNode));
        }
        r = &gpool[gpc++];
    }
    r->l = r->r = r->p = nil;
    r->k = k; r->c = 1;
    return r;
}
void release(TNode *p) {
    p->r = freelist;
    freelist = p;
}

TNode *search(BTree *tree, KEY v) {
    TNode *r = tree->root;
    int c;
    while(r!=nil) {
        c = kcmp(r->k, v);
        if (c==0) break;
        if (c>0) r = r->l;
        else r = r->r;
    }
    return r;
}

TNode *minimum(TNode *r) {
    while(r!=nil&&r->l!=nil) r=r->l;
    return r;
}

TNode *maximum(TNode *r) {
    while(r!=nil&&r->r!=nil) r=r->r;
    return r;
}

TNode *successor(TNode *r) {
    if (r->r!=nil) return minimum(r->r);
    TNode *p = r->p;
    while(p!=nil && r==p->r) {
        r = p; p = r->p;
    }
    return p;
}

TNode *predecessor(TNode *r) {
    if (r->l!=nil) return maximum(r->l);
    TNode *p = r->p;
    while(p!=nil && r==p->l) {
        r = p; p=r->p;
    }
    return p;
}

void left_rotate(BTree *tree, TNode *x) {
    TNode *y = x->r;
    x->r = y->l;
    if (y->l != nil) y->l->p = x;
    y->p = x->p;
    if (x->p==nil) tree->root = y;
    else if (x==x->p->l) x->p->l = y;
    else x->p->r=y;
    y->l = x;
    x->p = y;
}

void right_rotate(BTree *tree, TNode *y) {
    TNode *x = y->l;
    y->l = x->r;
    if (x->r != nil) x->r->p = y;
    x->p = y->p;
    if (y->p==nil) tree->root = x;
    else if (y==y->p->l) y->p->l = x;
    else y->p->r=x;
    x->r = y;
    y->p = x;
}

void insert_fixup(BTree *tree, TNode *z) {
    TNode *y;
    while(z->p->color == RED) {
        // red node should have parent
        if (z->p==z->p->p->l) {
            y = z->p->p->r;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z==z->p->r) {
                    z = z->p;
                    left_rotate(tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(tree, z->p->p);
            }
        } else {
            y = z->p->p->l;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z==z->p->l) {
                    z = z->p;
                    right_rotate(tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(tree, z->p->p);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(BTree *tree, KEY k, VALUE v) {
    // printf("insert %d,%d\n", k, v);
    TNode *p = nil, *np, *r = tree->root;
    int c;
    while(r!=nil) {
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
    if (p==nil) {
        tree->root = np;
    } else if (c>0) p->l = np;
    else p->r = np;
    np->color = RED;
    insert_fixup(tree, np);
    return;
}

void *transplant(BTree *tree, TNode *a, TNode *b) {
    if (a->p == nil) { tree->root = b; }
    else if (a->p->l == a) a->p->l = b;
    else a->p->r = b;
    b->p = a->p;
}

void delete_fixup(BTree *tree, TNode *x) {
    TNode *w;
    while(x!=tree->root && x->color==BLACK) {
        if (x==x->p->l) {
            w = x->p->r;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(tree, x->p);
                w = x->p->r;
            }
            if (w->l->color==BLACK && w->r->color==BLACK) {
                w->color = RED;
                x=x->p;
            } else { 
                if (w->r->color==BLACK) {
                    w->l->color=BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->p->r;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->r->color = BLACK;
                left_rotate(tree, x->p);
                x = tree->root;
            }
        } else if (x==x->p->r) {
            w = x->p->l;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(tree, x->p);
                w = x->p->l;
            }
            if (w->l->color==BLACK && w->r->color==BLACK) {
                w->color = RED;
                x=x->p;
            } else { 
                if (w->l->color==BLACK) {
                    w->r->color=BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->p->l;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->l->color = BLACK;
                right_rotate(tree, x->p);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}
void delete(BTree *tree, TNode *z) {
    if (z==nil) return;
    z->c--; if (z->c>0) return;
    TNode *y = z, *x;
    int color = y->color;
    if (z->l==nil) { 
        x = z->r;
        transplant(tree, z, z->r);
    } else if (z->r==nil) { 
        x = z->l;
        transplant(tree, z, z->l);
    } else {
        y = minimum(z->r);
        color = y->color;
        x = y->r;
        if (y->p == z) {
            // in case x is nil
            x->p = y;
        } else {
            transplant(tree, y, y->r);
            y->r = z->r;
            y->r->p = y;
        }
        transplant(tree, z, y);
        y->l = z->l;
        y->l->p = y;
        y->color = z->color;
    }
    if (color==BLACK) delete_fixup(tree, x);
    release(z);
}

void inorder(TNode *r) {
    if (r==nil) return ;
    inorder(r->l);
    printf("(%d,%d) ", r->k, r->v);
    inorder(r->r);
}



int main() {
    init(); 
    int i;
    char act[8];
    TNode *p;
    while(1) {
        scanf("%s", act); if (act[0]=='E') break;
        scanf("%d", &i);
        if (act[0]=='I') {
            insert(&gtree, i, i);
        } else if (act[0]=='Q') {
            p = search(&gtree, i);
            printf("%d:%d\n", i, p->c);
        } else if (act[0]=='D') {
            delete(&gtree, search(&gtree, i));
        }
    }
    return 0;
}


