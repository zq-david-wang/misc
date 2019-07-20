#include<stdio.h>

typedef struct _T {
    struct _T *left, *right;
    int s, e, mv, ml, mr, v;
}SNode;
SNode gpool[100000];
int gpc;
SNode *root;
SNode *flist;
SNode *alloc(int s, int e, int v) {
    SNode *r;
    if (flist) {
        r = flist;
        flist = flist->left;
    } else r = &gpool[gpc++];
    r->left = NULL;
    r->right = NULL;
    r->s = s; r->e = e; r->v = v;
    if (v==0) {
        r->mv = e-s+1;
        r->ml = e-s+1;
        r->mr = e-s+1;
    } else {
        r->mv = r->ml = r->mr = 0;
    }
    if (gpc>=sizeof(gpool)/sizeof(gpool[0]))printf("error\n");
    return r;
}
void init(int s, int e) {
    gpc = 0;
    flist = NULL;
    root = alloc(s, e, 0);
}
void release(SNode *r) {
    if (r==NULL) return;
    release(r->left);
    release(r->right);
    r->left = flist;
    flist = r;
}
void adjust(SNode *r) {
    if (r->right==NULL) return;
    // mergable
    if (r->right->right==NULL && r->left->left==NULL && r->right->v == r->left->v) {
        r->v = r->right->v;
        release(r->left);
        release(r->right);
        r->left = NULL;
        r->right = NULL;
        if (r->v==0) {
            r->mv = r->e-r->s+1;
            r->ml = r->e-r->s+1;
            r->mr = r->e-r->s+1;
        } else {
            r->mv = r->ml = r->mr = 0;
        }
        return;
    }
    r->mr = r->right->mr; if (r->right->mr==(r->right->e-r->right->s+1)) r->mr += r->left->mr;
    r->ml = r->left->ml; if (r->left->ml==(r->left->e-r->left->s+1)) r->ml += r->right->ml;
    r->mv = r->left->mr+r->right->ml;
    if (r->mv<r->right->mv) r->mv = r->right->mv;
    if (r->mv<r->left->mv) r->mv = r->left->mv;
}
void cover(SNode *r, int s, int e) {
    if (r->s==s&& r->e==e) {
        r->v = 1;
        release(r->left);
        release(r->right);
        r->left = r->right = NULL;
        r->mv = r->mr = r->ml = 0;
        return;
    }
    if (s<r->s || e>r->e || s>e) printf("[%d,%d] in [%d,%d] range error!!!\n", s ,e ,r->s, r->e);
    int m = (r->s+r->e)/2;
    if (r->left == NULL) {
        if (r->v==1) return;
        r->left = alloc(r->s, m, 0);
        r->right = alloc(m+1, r->e, 0);
    }
    if (e<=m) cover(r->left, s, e);
    else if (s>m) cover(r->right, s, e);
    else {
        cover(r->left, s, m);
        cover(r->right, m+1, e);
    }
    adjust(r);
    return;
}
int book(SNode *r, int d) {
    if (r==NULL || r->mv<d) return 0;
    if (r->s+d-1==r->e) {
        r->v = 1;
        r->mv = 0; r->ml = 0; r->mr = 0;
        return r->s;
    }
    int m = (r->s+r->e)/2;
    int s;
    if (d==0) printf("book error\n");
    if (r->left==NULL) {
        r->left = alloc(r->s, m, 0);
        r->right = alloc(m+1, r->e, 0);
    }
    if (r->left->mv >= d) {
        s = book(r->left, d);
    } else if (r->left->mr>0 && r->left->mr+r->right->ml >=d ) {
        s = r->left->e-r->left->mr+1;
        // printf("cross range left: [%d,%d]%d, right: [%d,%d]%d d:%d\n", r->left->s, r->left->e, r->left->mr, r->right->s, r->right->e, r->right->ml, d);
        cover(r->right, r->right->s, r->right->s+d-r->left->mr-1);
        cover(r->left, s, r->left->e);
    } else {
        s = book(r->right, d);
    }
    adjust(r);
    return s;
}

void revoke(SNode *r, int s, int e) {
    if (r==NULL) return;
    // printf("revoke %d,%d from [%d,%d]\n", s, e, r->s, r->e);
    if (r->s==s&&r->e==e) {
        r->v = 0;
        release(r->left);
        release(r->right);
        r->left = NULL;
        r->right = NULL;
        r->mv = r->mr = r->ml = e-s+1;
        return;
    }
    if (s<r->s||e>r->e||s>e) printf("revoke range error\n");
    int m = (r->s+r->e)/2;
    if (r->left==NULL) {
        if (r->v==0) return;
        r->left = alloc(r->s, m, 1);
        r->right = alloc(m+1, r->e, 1);
    }
    if (e<=m) revoke(r->left, s, e);
    else if (s>m) revoke(r->right, s, e);
    else {
        revoke(r->left, s, m);
        revoke(r->right, m+1, e);
    }
    adjust(r);
}
void printit(SNode *r, int d) {
    if (r==NULL) return;
    int i; for (i=0; i<4*d; i++) printf(" ");
    printf("[%d,%d] v:%d, mv:%d, ml: %d, mr: %d\n", r->s, r->e, r->v, r->mv, r->ml, r->mr);
    printit(r->left, d+1);
    printit(r->right, d+1);

}
int main() {
    int n, m, i, t, d, s;
    scanf("%d %d", &n, &m);
    init(1, n);
    for (i=0; i<m; i++) {
        scanf("%d", &t);
        if (t==1) {
            scanf("%d", &d);
            s = book(root, d);
            printf("%d\n", s);
        } else {
            scanf("%d %d", &s, &d);
            revoke(root, s, s+d-1);
        }
        // printit(root, 0);
    }
    return 0;
}
