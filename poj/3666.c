#include<stdio.h>
#include<stdlib.h>

int vs[2000], hs[2000];
int minv[2004];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int ary1[2004], ary2[2004];
#define INF 0x7fffffff
int findi(int v, int n) {
    int l = 0, h = n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (vs[m]==v) return m;
        if (vs[m]>v) h = m-1;
        else l = m+1;
    }
    return -1;
}
int main() {
    int n, i, h, hc, v, j, v1;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &h);
        vs[i] = h;
        hs[i] = h;
    }
    qsort(vs, n, sizeof(vs[0]), mycmp);
    hc = 0; for (i=0; i<n; i++) {
        if (i>0 && vs[i]==vs[i-1]) continue;
        vs[hc++] = vs[i];
    }
    for (i=0; i<n; i++) hs[i] = findi(hs[i], hc);
    int *dp = ary1, *dp1 = ary2, *tp;
    // nondecending
    for (i=0; i<hc; i++) dp[i] = 0;
    for (i=n-1; i>=0; i--) {
        // build min[i] -> j..his[i]
        minv[hs[i]+1] = INF;
        for (j=hs[i]; j>=0; j--) {
            v = dp[j]+vs[hs[i]]-vs[j];
            if (v>minv[j+1]) v = minv[j+1];
            minv[j] = v;
        }
        for (j=0; j<hc; j++) {
            if (hs[i]<=j) dp1[j] = dp[j]+vs[j]-vs[hs[i]]; 
            else {
                // j..hs[i] dp[k]+vs[hs[i]]-vs[k]
                dp1[j] = minv[j];
            }
        }
        tp = dp1; dp1 = dp; dp = tp;
        // for (j=0; j<hc; j++) printf("%d ", dp[j]); printf("\n");
    }
    v = dp[0]; for (i=1; i<hc; i++) if (v>dp[i]) v = dp[i];
    v1 = v;
    // reverse
    for (i=0; i<hc; i++) dp[i] = 0;
    for (i=n-1; i>=0; i--) {
        // build min[i] -> j..his[i]
        minv[hs[i]+1] = INF;
        for (j=hs[i]; j<hc; j++) {
            v = dp[j]+vs[j]-vs[hs[i]];
            if (j>hs[i]&&v>minv[j-1]) v = minv[j-1];
            minv[j] = v;
        }
        for (j=0; j<hc; j++) {
            if (hs[i]>=j) dp1[j] = dp[j]+vs[hs[i]]-vs[j]; 
            else {
                // hs[i]..j  dp[k]+vs[k]-vs[hs[i]]
                dp1[j] = minv[j];
            }
        }
        tp = dp1; dp1 = dp; dp = tp;
        // for (j=0; j<hc; j++) printf("%d ", dp[j]); printf("\n");
    }
    v = dp[0]; for (i=1; i<hc; i++) if (v>dp[i]) v = dp[i];
    if (v1>v) v1 = v;
    printf("%d\n", v1);
    return 0;
}
