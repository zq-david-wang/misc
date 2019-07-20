#include<stdio.h>
#include<stdlib.h>

#define MAX 100000
typedef struct _T{
    struct _T *left, *right, *p;
    int h, v, c, b;
}TNode;

TNode *root;
TNode *array[MAX];
int gac;
TNode gpool[MAX*2];
int gpc;
int gbc;
TNode *alloc(int v) {
    TNode *r = &gpool[gpc++];
    r->left = NULL;
    r->right = NULL;
    r->p = NULL;
    r->h = 1;
    r->v = v;
    r->c = 1;
    return r;
}
void init() {
    root = NULL;
    gpc = 0;
}

void inorder(TNode *r) {
    if (r==NULL) return;
    inorder(r->left);
    array[gac++] = r;
    inorder(r->right);
}

TNode *recon(int s, int e, TNode *parent) {
    if (s>e) return NULL;
    int m = (s+e)/2;
    TNode *p = array[m];
    p->left = recon(s, m-1, p);
    p->right = recon(m+1, e, p);
    p->p = parent;
    int hl = 0; if (p->left) hl = p->left->h;
    int hr = 0; if (p->right) hr = p->right->h;
    int h = hl; if (h<hr) h = hr;
    p->h = h+1;
    return p;
}

TNode* balance(TNode *r) {
    gac = 0;
    inorder(r);
    gbc += gac;
    return recon(0, gac-1, NULL);
}

int _insert(TNode *r, int v) {
    if (r==NULL) { printf("fatal error\n"); exit(1); return 0;}
    if (r->v == v) {
        r->c++;
        return 0;
    }
    int m;
    if (r->v>v) {
        if (r->left==NULL) { r->left = alloc(v); r->left->p = r; }
        else {
            m = _insert(r->left, v);
            if (m) {
                r->left = balance(r->left);
                r->left->p = r;
            }
        }
    } else {
        if (r->right==NULL) { r->right = alloc(v); r->right->p = r; }
        else {
            m = _insert(r->right, v);
            if (m) {
                r->right = balance(r->right);
                r->right->p = r;
            }
        }
    }
    int hl = 0; if (r->left) hl = r->left->h;
    int hr = 0; if (r->right) hr = r->right->h;
    int h = hl; if (h<hr) h = hr;
    r->h = h+1;
    h = hl-hr; if (h<0) h=-h;
    return h>8;
}


void insert(int v) {
    if (root==NULL) {
        root = alloc(v);
        return;
    }
    int m = _insert(root, v);
    if (m) {
        root = balance(root);
        root->p = NULL;
    }
}


void print(TNode *r) {
    if (r==NULL) return;
    print(r->left);
    printf("%d ", r->v);
    print(r->right);
}

TNode *find(TNode *r, int v) {
    while(r!=NULL) {
        if (r->v == v) return r;
        if (r->v > v) r= r->left;
        else r = r->right;
    }
    return NULL;
}

TNode *maxnode(TNode *r) {
    if (r->right==NULL) return r;
    return maxnode(r->right);
}

TNode *minnode(TNode *r) {
    if (r->left==NULL) return r;
    return minnode(r->left);
}


void calc_node(TNode *r) {
    int hl = 0; if (r->left) hl = r->left->h;
    int hr = 0; if (r->right) hr = r->right->h;
    int h = hl; if (h<hr) h = hr;
    r->h = h+1;
    h = hl-hr; if (h<0) h=-h;
    if (h>8) {
        TNode *p = r->p;
        if (r==root) { root = balance(r); root->p = NULL; }
        else {
            if (p->left == r) { p->left = balance(r); p->left->p = p; }
            else { p->right = balance(r); p->right->p = p; }
        }
    }
}


void remove_node(TNode *p) {
    p->c--;
    if (p->c > 0) return;
    TNode *mp;
    if (p->left) {
        mp = maxnode(p->left);
        p->v = mp->v;
        p->c = mp->c;
        if (mp->p->left == mp) { mp->p->left = mp->left; if (mp->left) mp->left->p = mp->p; }
        else { mp->p->right = mp->left; if (mp->left) mp->left->p = mp->p; }
        mp = mp->p;
    } else if (p->right) {
        mp = minnode(p->right);
        p->v = mp->v;
        p->c = mp->c;
        if (mp->p->left == mp) { mp->p->left = mp->right; if (mp->right) mp->right->p = mp->p; }
        else { mp->p->right = mp->right; if (mp->right) mp->right->p = mp->p; }
        mp = mp->p;
    } else {
        if (p==root) { root = NULL;}
        else {
            if (p->p->left == p) p->p->left = NULL;
            else p->p->right = NULL;
        }
        mp = p->p;
    }
    while(p!=NULL) {
        calc_node(p);
        p = p->p;
    }
}
typedef struct {int p, g;}CNode;
CNode cows[MAX];
CNode grass[MAX];
int mycmp(const void *a, const void *b) {
    return ((const CNode*)b)->g - ((const CNode*)a)->g;
}

int main() {
    init();
    int n, m, i, j, f;
    long long c=0;
    TNode *p, *target;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; i++) scanf("%d %d", &cows[i].p, &cows[i].g);
    for (i=0; i<m; i++) scanf("%d %d", &grass[i].p, &grass[i].g);
    qsort(cows, n, sizeof(cows[0]), mycmp);
    qsort(grass, m, sizeof(grass[0]), mycmp);
    j = 0; for (i=0; i<n; i++) {
        f = 0;
        while(j<m&&grass[j].g>=cows[i].g) {
            if (grass[j].p == cows[i].p) {
                j++;
                f = 1;
                c += grass[j].p;
                break;
            }
            insert(grass[j].p);
            j++;
        }
        if (f) continue;
        p = root;
        target = NULL;
        while(p!=NULL) {
            if (p->v == cows[i].p) {
                target = p;
                break;
            }
            if (p->v > cows[i].p) {
                if (target==NULL|| target->v > p->v) target = p;
                p = p->left;
            } else {
                p = p->right;
            }
        }
        if (target==NULL) { c = -1; break; }
        c += target->v;
        remove_node(target);
    }
    printf("%lld\n", c);
    return 0;
}

