#include<stdio.h>

typedef struct _T{
    struct _T *left, *right;
    int s, e, max, min;
}TNode;
TNode gpool[100000];
int gpc;
TNode *root;
TNode *alloc(int s, int e) {
    TNode *r = &gpool[gpc++];
    r->left = NULL;
    r->right = NULL;
    r->s = s;
    r->e = e;
    return r;
}
int hs[50001];
TNode *build(int s, int e) {
    TNode *r = alloc(s, e);
    if (s==e) {
        r->min = hs[s];
        r->max = hs[s];
        return r;
    }
    int m = (s+e)/2;
    r->left = build(s, m);
    r->right = build(m+1, e);
    r->max = r->left->max; if (r->max<r->right->max) r->max = r->right->max;
    r->min = r->left->min; if (r->min>r->right->min) r->min = r->right->min;
    return r;
}
void query(TNode *r, int s, int e, int *pmax, int *pmin) {
    if (s<r->s) s = r->s;
    if (e>r->e) e = r->e;
    if (r->s==s && r->e==e) {
        *pmax = r->max;
        *pmin = r->min;
        return;
    }
    int m = (r->s+r->e)/2;
    if (m>=e) return query(r->left, s, e, pmax, pmin);
    if (m<s) return query(r->right, s, e, pmax, pmin);
    int lmax, lmin, rmax, rmin;
    query(r->left, s, e, &lmax, &lmin);
    query(r->right, s, e, &rmax, &rmin);
    if (lmax<rmax) lmax = rmax;
    if (lmin>rmin) lmin = rmin;
    *pmax = lmax;
    *pmin = lmin;
}
int main() {
    gpc = 0;
    int n, q, i;
    int a, b, max, min;
    scanf("%d %d", &n, &q);
    for (i=1; i<=n; i++) scanf("%d", &hs[i]);
    root = build(1, n);
    for (i=0; i<q; i++) {
        scanf("%d %d", &a, &b);
        query(root, a, b, &max, &min);
        printf("%d\n", max-min);
    }

    return 0;
}
