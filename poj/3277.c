#include<stdio.h>
#include<stdlib.h>

struct {int a, b, h;}bs[40000];
int xs[80000];

int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}

int findi(int v, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (xs[m]==v) return m;
        if (xs[m]>v) h = m-1;
        else l = m+1;
    }
    return -1;
}
typedef struct _T {
    struct _T *left, *right;
    int s, e, h;
}SNode;
SNode gpool[80001];
int gpc;
SNode *root;
SNode *alloc() {
    SNode *r = &gpool[gpc++];
    r->left = NULL;
    r->right = NULL;
    r->h = 0;
    return r;
}
void init(int n) {
    gpc = 0;
    root = alloc();
    root->s = 1;
    root->e = n;
}
void addseg(SNode *r, int s, int e, int h) {
    int m;
    m = (r->s+r->e)/2; 
    SNode *p;
    if (r->left == NULL) {
        if (h<=r->h) return;
        if (r->s==s && r->e==e) {
            r->h = h;
            return;
        }
        p = alloc(); p->s = r->s; p->e = m; p->h = r->h; r->left = p;
        p = alloc(); p->s = m+1; p->e = r->e; p->h = r->h; r->right = p;
        if (r->h<h) r->h = h;
        if (s>m) addseg(r->right, s, e, h);
        else if (e<=m) addseg(r->left, s, e, h);
        else {
            addseg(r->left, s, m, h);
            addseg(r->right, m+1, e, h);
        }
    } else {
        if (r->s==s && r->e==e) {
            if (r->h<=h) {
                r->left = NULL;
                r->right = NULL;
                r->h = h;
            } else {
                addseg(r->left, s, m, h);
                addseg(r->right, m+1, e, h);            
            }
        } else {
            if (r->h<h) r->h = h;
            if (s>m) addseg(r->right, s, e, h);
            else if (e<=m) addseg(r->left, s, e, h);
            else {
                addseg(r->left, s, m, h);
                addseg(r->right, m+1, e, h);
            }
        }
    }

}
long long count(SNode *r) {
    if (r->left == NULL) {
        long long c = xs[r->e]-xs[r->s-1];
        c *= r->h;
        return c;
    }
    return count(r->left) + count(r->right);
}

int main() {
    int n, i, c=0, nc=0;
    int ai, bi;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d %d %d", &bs[i].a, &bs[i].b, &bs[i].h);
    for (i=0; i<n; i++) {
        xs[c++] = bs[i].a;
        xs[c++] = bs[i].b;
    }
    qsort(xs, c, sizeof(xs[0]), mycmp);
    for (i=0; i<c; i++) {
        if (i>0 && xs[i]==xs[i-1]) continue;
        xs[nc++] = xs[i];
    }
    init(nc-1);
    for (i=0; i<n; i++) {
        ai = findi(bs[i].a, nc);
        bi = findi(bs[i].b, nc);
        addseg(root, ai+1, bi, bs[i].h);
    }
    long long r = count(root);
    printf("%lld\n", r);
    return 0;
}
