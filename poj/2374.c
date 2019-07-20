#include<stdio.h>
#include<string.h>

typedef struct _T {
    struct _T *left, *right;
    int s, e, i;
}Seg;
Seg gpool[800000];
int gpc;

Seg *root;
Seg *alloc(int s, int e) {
    Seg *r = &gpool[gpc++];
    r->left = NULL;
    r->right = NULL;
    r->i = -1;
    r->s = s;
    r->e = e;
    return r;
}
int sss[50004][2];
int iis[50004][2];
int dp[50004][2];

int dfs(int n, int d) {
    if (n==0) return 0;
    if (dp[n][d] != -1) return dp[n][d];
    int nn = iis[n][d];
    int d1, d2;
    if (nn==0) {
        d1 = sss[n][d];
        if (d1<0) d1 = -d1;
    } else {
        d1 = sss[n][d]-sss[nn][0]+dfs(nn, 0);
        d2 = sss[nn][1]-sss[n][d]+dfs(nn, 1);
        if (d1>d2)d1 =d2;
    }
    dp[n][d] = d1;
    // printf("dp %d, %d is %d\n", n, d, d1);
    return d1;
}
int find(Seg* r, int v) {
    if (r==NULL) printf("fail to find %d\n", v);
    if (r->i != -1) return r->i;
    int m = (r->s+r->e)/2;
    if (m==r->e)m--;
    if (v<=m) return find(r->left, v);
    return find(r->right, v);
}
void insert(Seg*r, int s, int e, int i) {
    if (s>e) return;
    if (s>r->e || e<r->s) return;
    if (s<=r->s && e>=r->e) {
        // printf("fill %d->%d by (%d,%d)with %d\n", r->s, r->e,s ,e, i);
        r->i = i; return;
    }
    int m = (r->s+r->e)/2;
    if (m==r->e) m--;
    if (r->left==NULL) {
        r->left=alloc(r->s, m);
    }
    if (r->right==NULL) {
        r->right=alloc(m+1, r->e);
    }
    if (r->i>=0) {
        r->left->i = r->i;
        r->right->i = r->i;
    }
    if (s<r->s) s = r->s;
    if (e>r->e) e = r->e;
    r->i = -1;
    insert(r->left, s, e, i);
    insert(r->right, s, e, i);
}
int main() {
    int n, s, i, a, b;
    gpc = 0;
    root = alloc(-100000, 100000);
    root->i = 0;
    scanf("%d %d", &n, &s);
    for (i=1; i<=n; i++) { 
        scanf("%d %d", &a, &b);
        iis[i][0] = find(root, a); iis[i][1] = find(root, b);
        // printf("iis %d %d\n", iis[i][0], iis[i][1]);
        insert(root, a+1, b-1, i);
        sss[i][0] = a; sss[i][1] = b;
    }
    memset(dp, 0xff, sizeof(dp));
    a = s-sss[n][0] + dfs(n, 0);
    b = sss[n][1]-s + dfs(n, 1);
    if (a>b) a = b; printf("%d\n", a);
    return 0;
}

