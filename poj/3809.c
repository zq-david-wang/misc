#include<stdio.h>
#include<stdlib.h>
#include<string.h>


short fs[256];
char flag[16];
char dp[177147];
int db[16];
int dfs(int m, int bn, int gn) {
    if (dp[m]!=-1) return dp[m];
    int mask=0, v=0, t=m, c;
    int c1, c2;
    int i; for (i=0; i<bn; i++) {
        c=t%3;  t/=3;
        if (c==0) mask |= (1<<i);
        else { c--; if (c) v|=(1<<i);}
    }
    mask = ~mask;
    c=0; for (i=0; i<gn; i++) {
        if ((fs[i]&mask)==v) c++;
    }
    int r=16;
    if (c>1) {
        for (i=0; i<bn; i++) {
            if ((mask&(1<<i))) continue;
            c1 = dfs(m+db[i], bn, gn);
            c2 = dfs(m+db[i]+db[i], bn, gn);
            if (c1<c2) c1=c2; c1++;
            if (r>c1) r=c1;
        }
    } else r=0;
    dp[m]=r;
    // printf("dfs %d(%x)==>%d\n", m, mask, r);
    return r;
}
int main() {
    int m, n, i, v, j;
    char ft[16];
    db[0]=1; for (i=1; i<16; i++) db[i]=3*db[i-1];
    while(1) {
        scanf("%d %d", &m, &n); if (m==0&&n==0) break;
        for (i=0; i<n; i++) {
            scanf("%s", ft);
            v=0; for (j=0; j<m; j++) v = v*2+ft[j]-'0';
            fs[i]=v;
        }
        memset(dp, 0xff,sizeof(dp));
        i = dfs(0, m, n);
        printf("%d\n", i);
    }
    return 0;
}


