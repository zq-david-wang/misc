#include<stdio.h>
#include<string.h>


int ifs[256], efs[256];
int dp[256][256];
int sum[256][256];

/*
int dfs(int s, int e) {
    if (s>e) return 0;
    if (dp[s][e] != -1) return dp[s][e];
    int i;
    int c, rc=-1;
    for (i=s; i<=e; i++) {
        c = sum[s][e]-ifs[i];
        c += dfs(s, i-1);
        c += dfs(i+1, e);
        if (rc<0 || rc>c) rc = c;
    }
    dp[s][e]=rc;
    return rc;
}
*/

int main() {
    int n, i, r, j, k;
    int s, cc, c;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) scanf("%d", &ifs[i]);
        for (i=0; i<=n; i++) scanf("%d", &efs[i]);
        for (i=0; i<n; i++) {
            s=efs[i];
            for (j=i; j<n; j++) {
                s+= ifs[j]; s+=efs[j+1];
                sum[i][j] = s;
            }
        }
        for (i=0; i<n; i++) { dp[i][0]=0; dp[i][1]=efs[i]+efs[i+1]; }
        for (k=2; k<=n; k++) {
            for (i=0; i+k<=n; i++) {
                s = sum[i][i+k-1];
                cc = -1;
                for (j=0; j<k; j++) {
                    c = s-ifs[i+j]+dp[i][j]+dp[i+j+1][k-1-j];
                    if (cc<0 || cc>c) cc=c;
                }
                dp[i][k] = cc;
            }
        }
        // memset(dp, 0xff, sizeof(dp));
        // s = dfs(0, n-1);
        s = dp[0][n];
        for (i=0; i<n; i++) s+=ifs[i];
        printf("%d\n", s);
    }
    return 0;
}
