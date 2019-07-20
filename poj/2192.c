#include<stdio.h>
#include<string.h>

char ba[256], bb[256], bc[512];
char dp[256][256];
char dfs(int i1, int i2) {
    if (ba[i1]==0 && bb[i2]==0) return 1;
    if (dp[i1][i2]!=-1) return dp[i1][i2];
    char r=0; if (ba[i1]==bc[i1+i2]) r=dfs(i1+1, i2);
    if (r==0 && bb[i2]==bc[i1+i2]) r=dfs(i1, i2+1);
    dp[i1][i2]=r;
    return r;
}
int main() {
    int c, i, k, j;
    scanf("%d", &c); for (i=1; i<=c; i++) {
        scanf("%s %s %s", ba, bb, bc);
        memset(dp, 0xff, sizeof(dp));
        if (dfs(0, 0)) printf("Data set %d: yes\n", i); 
        else printf("Data set %d: no\n", i);
    }
    return 0;
}
