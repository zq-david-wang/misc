#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { short p, d; }SNode;
SNode app1[300], app2[300];
int gn, dp[300][300];
int racc1[301], racc2[301];
int dfs(int i1, int i2) {
    if (i1==gn) return racc2[i2];
    if (i2==gn) return racc1[i1];
    if (dp[i1][i2] != -1) return dp[i1][i2];
    int r=0;
    int ts[10]={0};
    int i=i1, j=i2;
    int t1=0, t2=0, p;
    while(1) {
       if (i==gn && j==gn) break; 
       if (j==gn || (i<gn && t1<=t2)) {
           p = app1[i].p;
           if (ts[p]>t1) { j--; t1+=app1[i].d; break; }
           t1 += app1[i].d;
           ts[p] = t1;
           i++;
       } else if (i==gn||(j<gn&&t1>t2)) {
           p = app2[j].p;
           if (ts[p]>t2) { i--; t2+=app2[j].d; break; }
           t2 += app2[j].d;
           ts[p] = t2;
           j++;
       }
    }
    if (i==gn||j==gn) {
        // no conflict
        r = racc1[i1]; if (r<racc2[i2]) r=racc2[i2];
    } else {
        r = t2+dfs(i, j+1);
        int t = t1+dfs(i+1, j);
        if (r>t) r=t;
    }
    dp[i1][i2]=r;
    return r;
}
int main() {
    int tc, ti, n, i, j, p, d;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &n);
        for (i=0; i<n; i++) {
            scanf("%d %d", &p, &d);
            app1[i].p=p; app1[i].d=d;
        }
        racc1[n]=0; for (i=n-1; i>=0; i--) racc1[i]=racc1[i+1]+app1[i].d;
        for (i=0; i<n; i++) {
            scanf("%d %d", &p, &d);
            app2[i].p=p; app2[i].d=d;
        }
        racc2[n]=0; for (i=n-1; i>=0; i--) racc2[i]=racc2[i+1]+app2[i].d;
        memset(dp, 0xff, sizeof(dp));
        gn = n;
        i = dfs(0, 0);
        printf("%d\n", i);
    } 
    return 0;
}


