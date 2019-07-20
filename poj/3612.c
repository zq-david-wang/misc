#include<stdio.h>

int hs[100000];
int ary1[101], ary2[101];
int maxvs[102], minvs[102];
#define INF 0x7fffffff
int main() {
    int n, c, i, j;
    int v1, v2, cv;
    int mh = 0;
    scanf("%d %d", &n, &c);
    for (i=0; i<n; i++) {
        scanf("%d", &hs[i]);
        if (mh<hs[i]) mh = hs[i];
    }
    int *dp, *dp1, *tp;
    dp = ary1; dp1 = ary2;
    for (i=hs[n-1]; i<=mh; i++) dp[i] = 0;
    for (i=0; i<hs[n-1]; i++) dp[i] = INF;
    for (i=n-2; i>=0; i--) {
        minvs[mh+1] = INF;
        for (j=mh; j>=hs[i+1]; j--) {
            if (dp[j]==INF) cv = INF;
            else cv = dp[j]+(j-hs[i+1])*(j-hs[i+1]);
            if (minvs[j+1]==INF) minvs[j] = INF;
            else minvs[j] = minvs[j+1]+c;
            if (cv<minvs[j]) minvs[j] = cv;
        }
        for (;j>0; j--) if (minvs[j+1]==INF) minvs[j] = INF; else minvs[j] = minvs[j+1]+c;
        for (j=0; j<hs[i+1]; j++) maxvs[j] = INF;
        for (j=hs[i+1]; j<=mh; j++) {
            if (dp[j]==INF) cv = INF;
            else cv = dp[j]+(j-hs[i+1])*(j-hs[i+1]);
            if (maxvs[j-1] == INF) maxvs[j] = INF;
            else maxvs[j] = maxvs[j-1]+c;
            if (cv<maxvs[j]) maxvs[j] = cv;
        }
        // printf("min %d: ", i);  for (j=1; j<=mh; j++) printf("%d ", minvs[j]);printf("\n");
        // printf("max %d: ", i);  for (j=1; j<=mh; j++) printf("%d ", maxvs[j]);printf("\n");
        for (j=hs[i]; j<=mh; j++) {
            v1 = minvs[j];
            v2 = maxvs[j];
            if (v1>v2) v1 = v2;
            dp1[j] = v1;
            // printf("dp %d/%d ==> %d\n", i, j, v1);
        }
        for (j=1; j<hs[i]; j++) dp1[j] = INF;
        /* 
        for (; j<=mh; j++) {
            v1 = INF;
            int k, d; for (k=hs[i+1]; k<=mh; k++) {
                d = k-j; if (d<0) d=-d;
                cv = d*c+dp[k]+(k-hs[i+1])*(k-hs[i+1]);
                if (cv<v1) v1 = cv;
            }
            dp1[j] = v1;
        }
        */
        tp = dp; dp = dp1; dp1 = tp;
    }
    v1 = dp[hs[0]];
    for (i=hs[0]+1; i<=mh; i++) {
       cv = (i-hs[0])*(i-hs[0])+dp[i]; 
       if (cv<v1) v1 = cv;
    }
    printf("%d\n", v1);
    return 0;
}
