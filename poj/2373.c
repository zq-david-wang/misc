#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {int s,e; } Cow;
Cow cows[1000];
int dp[1000004];
short mark[1000004];
int mycmp(const void *a, const void *b) {
    return ((const Cow*)a)->s - ((const Cow*)b)->s;
}

int ga, gb, gl;
int dfs(int c) {
    if (c>gl) return -2;
    if (dp[c] != -1) return dp[c];
    int mi = mark[c];
    int r = -2, i, tc, tr;
    if (mi < 0 || cows[mi].s == c) {
        for (i=ga; i<=gb; i++) {
            tc = i*2;
            tr = dfs(c+tc);
            if (tr<0) continue;
            tr++;
            if (r<0 || r>tr) r = tr;
        }
    }
    dp[c] = r;
    printf("dfs %d==>%d\n", c, r);
    return r;
}

int main() {
    int n, l, a, b;
    int i, j, e;
    scanf("%d %d %d %d", &n, &l, &a, &b);
    for (i=0; i<n; i++) scanf("%d %d", &cows[i].s, &cows[i].e);
    qsort(cows, n, sizeof(Cow), mycmp);
    j=0; e=cows[0].e; for (i=1; i<n; i++) {
        if (cows[i].s<e) {
            if (cows[i].e > e) e = cows[i].e;
        } else {
            cows[j++].e = e;
            cows[j].s = cows[i].s;
            e = cows[i].e;
        }
    }
    cows[j++].e = e;
    n = j;
    memset(mark, 0xff, sizeof(mark[0])*(l+1));
    for (i=0; i<n; i++) { for (j=cows[i].s; j<cows[i].e;j++) mark[j] = i; }
    memset(dp, 0xff, sizeof(dp));
    ga = a; gb = b; gl = l;
    a *= 2; b *= 2;
    dp[l] = 0;
    for (i=l-1; i>l-a; i--) {
        dp[i] = -1;
    }
    int mi;
    for (;i>=0; i--) {
        dp[i] = -1;
        if (i&1) continue;
        mi = mark[i];
        if (mi<0 || i==cows[mi].s) {
            j = b;
            if (i+j>l) j = (l-i)/2*2;
            for (; j>=a; j-=2) {
                if (dp[i+j]<0) continue;
                dp[i] = 1+dp[i+j];
                break;
            }
        }
    }
    printf("%d\n", dp[0]);
    return 0;
}
