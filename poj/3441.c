#include<stdio.h>
#include<string.h>

char book[128][32];
short dp[128][32];
short record[128][32];
int gn, gend;
int dfs(int sd, int ri) {
    if (sd==gend) return 0;
    if (book[sd][ri]=='X') return -2;
    if (dp[sd][ri]!=-1) return dp[sd][ri];
    int r=-2, tr;
    // r = dfs(sd+1, ri);
    // record[sd][ri]=ri;
    int i; for (i=0; i<gn; i++) {
        tr = dfs(sd+1, i); if (tr>=0) {
            if (i!=ri) tr++;
            if (r<0||r>tr) {
                r = tr; record[sd][ri]=i;
            }
        }
    }
    // printf("dfs %d,%d ==> %d (%d)\n", sd, ri, r, record[sd][ri]);
    dp[sd][ri]=r;
    return r;
}
int main() {
    int n, m, i, ci=0, ni;
    int a, b, si, r, c;
    while(1) {
        scanf("%d %d", &m, &n); if (m==0) break; ci++;
        if (ci>1) printf("\n");
        printf("Case %d:\n\n", ci);
        for (i=0; i<m; i++) scanf("%s", book[i]);
        scanf("%d %d", &a, &b);
        a--; b--;
        r = -1;
        memset(dp, 0xff, sizeof(dp));
        gn=n; gend=b;
        for (i=0; i<n; i++) {
            if (book[a][i]=='O') {
                c = dfs(a, i);
                if(c<0) continue;
                if (r<0||r>c) { r=c; si=i; }
            }
        }
        if (r<0) printf("Not available\n");
        else {
            i=a; 
            while(i<b) {
                ni = record[i][si];
                if (ni!=si) {
                    printf("%c: %d-%d\n", si+'A', a+1, i+2);
                    a = i+1; si=ni;
                }
                i++;
            }
            printf("%c: %d-%d\n", si+'A', a+1, i+1);
        }
    }
    return 0;
}
