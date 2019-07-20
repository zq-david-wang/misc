#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cs[40];
typedef struct { short h, t; } BNode;
BNode books[80];
#define MAX 731
short dp[MAX][MAX][31];
int gn, gj, gs;
int dfs(int i1, int i2, int s) {
    if (i1>=MAX||i2>=MAX) return MAX;
    if (s==31) {
        int i3 = gs-i1-i2;
        if (i3<i1) i3=i1;
        if (i3<i2)  i3=i2;
        return i3;
    } 
    if (dp[i1][i2][s]!=-1) return dp[i1][i2][s];
    int i, j, n=cs[s];
    int d1=i1, d2, r=MAX, t;
    for (i=0; i<=n; i++) {
        if (d1>=MAX) break;
        d2 = i2;
        for (j=0; j+i<=n; j++) {
            if (d2>=MAX) break;
            t = dfs(d1, d2, s+1);
            if (r>t) r=t;
            d2 += s;
        }
        d1 += s;
    }
    dp[i1][i2][s]=r;
    return r;
}

int main() {
    int tc, ti, n, j, i, h, t;
    int rs, ccs, cw;
    int h1, h2, h3, t1, t2, t3;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &n);
        for (i=0; i<=30; i++) cs[i]=0;
        gs=0;
        for (i=0; i<n; i++) {
            scanf("%d %d", &h, &t);
            for (j=i-1; j>=0; j--) {
                if (books[j].h>=h) break;
                books[j+1]=books[j];
            }
            books[j+1].h=h;
            books[j+1].t=t;
            gs+=t;
            cs[t]++;
        }
        gn=n;
        h1=books[0].h;
        t1=books[0].t;
        cs[books[0].t]--;
        rs = 0x7fffffff;
        for (i=1; i<n-1; i++) {
            h2 = books[i].h;
            t2 = books[i].t;
            cs[t2]--;
            for (j=i+1; j<n; j++) {
                cs[books[j].t]--;
                h3 = books[j].h;
                memset(dp, 0xff, sizeof(dp));
                cw = dfs(t1, t2, 0);
                ccs = cw*(h1+h2+h3);
                if (rs>ccs) rs=ccs;
                cs[books[j].t]++;
            }
            t1+= books[i].t;
        }
        printf("%d\n", rs);
    }
    return 0;
}


