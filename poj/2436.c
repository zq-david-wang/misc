#include<stdio.h>
#include<string.h>

short cows[1000];
short dp[32768][1000];
char omap[32768];
short ones(int m) {
    int c = 0;
    while(m) {
        m &= (m-1);
        c++;
    }
    return c;
}
void build() {
    int i; 
    for (i=0; i<32768; i++) {
        omap[i] = ones(i);
    }
}
int gn, gk;
short dfs(int m, int s) {
    if (omap[m]>gk) return -2;
    if (s==gn) return 0;
    if (dp[m][s] != -1) return dp[m][s];
    short r = dfs(m, s+1);
    short r2 = dfs(m|cows[s], s+1);
    if (r2>=0) {
        r2++;
        if (r<r2) r = r2;
    }
    dp[m][s] = r;
    return r;
}
int main() {
    int n, d, k, i, m, j, v, b, nn;
    int rc = 0;
    build();
    scanf("%d %d %d", &n, &d, &k);
    nn = 0; for (i=0; i<n; i++) {
        scanf("%d", &m);
        v = 0;
        for (j=0; j<m; j++) {
            scanf("%d", &b);
            v |= (1<<(b-1));
        }
        if (v==0) rc++;
        else cows[nn++] = v;
    }
    // memset(dp, 0xff, sizeof(dp));
    m = 0;
    for (i=0; i<32768; i++) {
        if (omap[i]!=k) continue;
        b = 0;
        for (j=0; j<nn; j++) {
            if ((cows[j]|i) == i) b++;
        }
        if (m<b) m = b;
    }
    // gn = nn; gk = k;
    // v = dfs(0, 0);
    // if (v>0) rc += v;
    rc += m;
    printf("%d\n", rc);
    return 0;
}
