#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{ int r, c; }CNode;
CNode cows[1000];
int rcs[1001][2];
int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    return pa->c-pb->c;
}
int dp[1001][1001][5];
int gn;
char cs[5] = {0, 1, 1, 2, 2};
int dfs(int s, int k, int p) {
    if (k<0) return -2;
    if (s>=gn) {
        return 0;
    }
    if (dp[s][k][p] != -1) return dp[s][k][p];
    int i, c, tr, r=-2, d=0;
    if (s>0) d = cows[s].c-cows[s-1].c;
    c = cows[s].r;
    r = dfs(s+1, k-1, c);
    if (r>=0) r+=cs[c];
    if (c!=3) {
        tr = dfs(s+1, k-1, 3);
        if (tr>=0) { tr+=2; if (r<0 || r>tr) r=tr; }
    }
    if (c==1) {
        if (p==0) {
            tr = dfs(s+1, k-1, 1);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else if (p==1) {
            tr = dfs(s+1, k, 1);
            if (tr>=0) { tr += d; if (r<0 || r>=tr) r = tr; }
        } else if (p==2) {
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 1);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else if (p==3) {
            tr = dfs(s+1, k, 3);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 1);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else {
            tr = dfs(s+1, k, 4);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k, 1);
            if (tr>=0) { tr += d; if (r<0 || r>=tr) r = tr; }
        }
    } else if (c==2) {
        if (p==0) {
            tr = dfs(s+1, k-1, 2);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else if (p==1) {
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 2);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else if (p==2) {
            tr = dfs(s+1, k, 2);
            if (tr>=0) { tr += d; if (r<0 || r>=tr) r = tr; }
        } else if (p==3) {
            tr = dfs(s+1, k, 3);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 2);
            if (tr>=0) { tr += 1; if (r<0 || r>=tr) r = tr; }
        } else {
            tr = dfs(s+1, k, 4);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k, 2);
            if (tr>=0) { tr += d; if (r<0 || r>=tr) r = tr; }
        }
    } else {
        if (p==0) {
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
        } else if (p==1) {
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
        } else if (p==2) {
            tr = dfs(s+1, k-1, 3);
            if (tr>=0) { tr += 2; if (r<0 || r>=tr) r = tr; }
            tr = dfs(s+1, k-1, 4);
            if (tr>=0) { tr += 1+d; if (r<0 || r>=tr) r = tr; }
        } else if (p==3) {
            tr = dfs(s+1, k, 3);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
        } else {
            tr = dfs(s+1, k, 4);
            if (tr>=0) { tr += 2*d; if (r<0 || r>=tr) r = tr; }
        }
    }
    dp[s][k][p] = r;
    // printf("dp %d(%d),%d,%d ==> %d  (%d)\n", s, cows[s].r, k, p, r, d);
    return r;
}
int main() {
    int n, k, b, i, j;
    scanf("%d %d %d", &n, &k, &b);
    for (i=0; i<n; i++) {
        scanf("%d %d", &cows[i].r, &cows[i].c);
    }
    qsort(cows, n, sizeof(cows[0]), mycmp);
    j=0; for (i=0; i<n; i++) {
        if (i>0 && cows[i].c==cows[i-1].c) {
            cows[j-1].r |= (1<<(cows[i].r-1));
            continue;
        }
        if (j!=i) cows[j] = cows[i];
        j++;
    }
    n = j;
    // for (i=0; i<n; i++) printf("%d: %d/%d\n", i, cows[i].c, cows[i].r);
    memset(dp, 0xff, sizeof(dp));
    gn = n;
    int r = dfs(0, k, 0);
    printf("%d\n", r);
    return 0;
}
