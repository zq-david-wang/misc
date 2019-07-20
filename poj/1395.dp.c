#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MOD 100000
#define MAX 10000
int  gcd(int a, int b) {
    int t; while(a) {
        t=a; a=b%a; b=t;
    }
    return b;
}
int cogs[32];
int primes[] = {2,3,5,7,11,13,17,19};
char cf[32];
char dp[32][32][32][32];
char cans[32][4], as[4], bs[4];
int canc;
char dfs(int a, int b, int c, int d) {
    if (dp[a][b][c][d]!=-1) return dp[a][b][c][d];
    int i, j, r=0;
    int vs[4]; vs[0]=a; vs[1]=b; vs[2]=c; vs[3]=d;
    for (i=0; i<canc; i++) {
        for (j=0; j<4; j++) if (cans[i][j]>vs[j]) break;
        if (j<4) continue;
        r = dfs(a-cans[i][0], b-cans[i][1], c-cans[i][2], d-cans[i][3]);
        if (r) break;
    }
    dp[a][b][c][d] = r;
    return r;
}
int main() {
    int tc, ti, n, i, m, a, b, j, v, k, c;
    int ca, cb, g;
    int min, r, ii, f;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        scanf("%d", &n);
        min = MAX; 
        for (i=0; i<n; i++) {
            scanf("%d", &cogs[i]);
            if (min>cogs[i]) min=cogs[i];
        }
        for (i=0; i<=20; i++) cf[i]=0;
        for (i=0; i<n; i++) { cogs[i]/=min; cf[cogs[i]]=1; }
        memset(dp, 0xff, sizeof(dp)); dp[0][0][0][0]=1;
        k=0; for (i=0; i<n; i++) {
            for (j=0; j<4; j++) if ((cogs[i]%primes[j])==0) break;
            if (j<4) {
                for (j=0; j<4; j++) {
                    c=0; while((cogs[i]%primes[j])==0) { c++; cogs[i]/=primes[j]; }
                    cans[k][j]=c;
                }
                k++;
            }
        }
        canc = k;
        scanf("%d", &m);
        if (ti>1) printf("\n");
        printf("Scenario #%d:\n", ti);
        for (i=0; i<m; i++) {
            scanf("%d %d", &a, &b);
            g=gcd(a, b); ca = a/g; cb=b/g;
            for (j=4; j<8; j++) {
                if ((ca%primes[j])==0 || (cb%primes[j])==0) {
                    if (cf[primes[j]]==0) break;
                }
            }
            if (j<8) {
                printf("Gear ratio %d:%d cannot be realized.\n", a, b);
                continue;
            }
            for (j=0; j<4; j++) {
                c=0; while((ca%primes[j])==0) { c++; ca/=primes[j]; } as[j]=c;
                c=0; while((cb%primes[j])==0) { c++; cb/=primes[j]; } bs[j]=c;
            }
            for (j=0; j<4; j++) {
                if (bs[j]==0) continue;
                for (k=0; k<canc; k++) {
                    if (cans[k][j]) break;
                }
                if (k==canc) break;
                f = (bs[j]+cans[k][j]-1)/cans[k][j];
                for (ii=0; ii<4; ii++) {
                    r = cans[k][ii]*f;
                    if (bs[ii]>=r) bs[ii]-=r;
                    else {
                        as[ii]+=(r-bs[ii]);
                        bs[ii]=0;
                    }
                }
            }
            if (j<4) {
                printf("Gear ratio %d:%d cannot be realized.\n", a, b);
                continue;
            }
            j = dfs(as[0], as[1], as[2], as[3]);
            if (j) printf("Gear ratio %d:%d can be realized.\n", a, b);
            else printf("Gear ratio %d:%d cannot be realized.\n", a, b);
        }
    }
    return 0;
}


