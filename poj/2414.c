#include<stdio.h>

int dp[2048][20];
char buf[1024][1024];
char ci[128], *syms="ARNDCQEGHILKMFPSTWYV";
int queue[2048];
int mi[2048], mv[2048];
char flag[2048];
char rs[1024];
#define INF 0x7fffffff
int main() {
    int n, l, i, s, k, j;
    int head, tail;
    char c;
    int mm, mmi, cc, m1, m2;
    int p, c1, c2;
    int rc=0;
    for (i=0; i<20; i++) ci[syms[i]]=i;
    while(1) {
        scanf("%d %d", &n, &l);
        if (n==0 && l==0) break;
        s = n-1;
        rc = 0;
        for (i=0; i<n; i++) scanf("%s", buf[i]);
        for (k=0; k<l; k++) {
            head=tail=0;
            for (i=0; i<n+n; i++) flag[i] = 0;
            for (i=0; i<n; i++) {
                for (j=0; j<20; j++) dp[s+i][j] = INF;
                c = ci[buf[i][k]];
                dp[s+i][c] = 0;
                queue[head++] = s+i;
                mi[s+i] = c;
                mv[s+i] = 0;
            }
            while(tail<head) {
                i = queue[tail++];
                if (i==0) break;
                p = (i-1)/2;
                if (flag[p]) continue;
                flag[p] = 1;
                c1 = p*2+1; c2=p*2+2;
                mm = INF;
                for (j=0; j<20; j++) {
                    m1 = mv[c1]; if (j!=mi[c1]) m1++;
                    if (m1>dp[c1][j]) m1=dp[c1][j];
                    m2 = mv[c2]; if (j!=mi[c2]) m2++;
                    if (m2>dp[c2][j]) m2=dp[c2][j];
                    m1 += m2;
                    dp[p][j] = m1;
                    if (mm>m1) { mm=m1; mmi=j; }
                }
                mv[p] = mm;
                mi[p] = mmi;
                queue[head++] = p;
            }
            // printf("%d: %d %d\n", k ,mi[0], mv[0]);
            rs[k]=syms[mi[0]];
            rc += mv[0];
        }
        rs[k]=0;
        printf("%s %d\n", rs, rc);
    }
    return 0;
}
