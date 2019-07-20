#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    short s, f;
}CNode;
CNode cows[100];
int dp[200001];
#define INF 0x7fffffff
int main() {
    int n, i;
    int s, f, mss=0, mmss=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &s, &f);
        cows[i].s = s;
        cows[i].f = f;
        if (s>0) mss+=s;
        if (s<0) mmss+=s;
    }
    for (i=0; i<=mss-mmss; i++) dp[i] = -INF;
    dp[-mmss] = 0;
    int v, t, dpi, dpj, j;
    for (i=n-1; i>=0; i--) {
        if (cows[i].s >=0) {
            for (j=mss; j>=mmss; j--) {
                if (j-cows[i].s<mmss) break;
                dpi = j-mmss;
                dpj = j-cows[i].s-mmss;
                v = dp[dpi];
                if (dp[dpj] != -INF) {
                    t = dp[dpj]+cows[i].f;
                    if (v<t) v = t;
                }      
                dp[dpi] = v;
            } 
        } else {
            for (j=mmss; j<=mss; j++) {
                if (j-cows[i].s>mss) break;
                dpi = j-mmss;
                dpj = j-cows[i].s-mmss;
                v = dp[dpi];
                if (dp[dpj] != -INF) {
                    t = dp[dpj]+cows[i].f;
                    if (v<t) v = t;
                }
                dp[dpi] = v;
            }
        }
    }
    // for (i=0; i<n; i++) printf("%d:%d,%d  maxs %d\n", i, cows[i].s, cows[i].f, max1[i]);
    s = 0; for (i=0; i<=mss; i++) {
        f = dp[i-mmss];
        if (f>=0 && (f+i)>s) s = f+i;
    }
    printf("%d\n", s);
    return 0;
}
