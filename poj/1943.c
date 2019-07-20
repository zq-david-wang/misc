#include<stdio.h>
#include<string.h>

#define MOD 5040
struct {short p, q;}room[128];
char stay[102][MOD+1];
int dp[102][MOD+1];

int gn, gmod;
int dfs(int r, int d) {
    if (r==gn+1) return 0;
    d %= gmod;
    if (stay[r][d]==0) return -2;
    if (dp[r][d] != -1) return dp[r][d];
    dp[r][d] = -2;
    int t = dfs(r, d+1), tt;
    if (t>=0) t++;
    if (r>0) { tt = dfs(r-1, d+1); if (tt>=0) { tt++; if (t<0||t>tt)t=tt; } }
    if (r<=gn) { tt = dfs(r+1, d+1); if (tt>=0) { tt++; if (t<0||t>tt)t=tt; } }
    dp[r][d] = t;    
    // printf("dfs %d,%d ==> %d\n", r, d, t);
    return t;
}

int main() {
    int n, i, j, k, v, c;
    char twoc, threec, fivec, sevenc;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        twoc=threec=fivec=sevenc=0;
        for (i=1; i<=n; i++) {
            scanf("%d", &v);
            room[i].p = v;
            if (v==0) continue;
            c=0; while((v%2)==0) { v/=2; c++; } if (twoc<c) twoc=c;
            c=0; while((v%3)==0) { v/=3; c++; } if (threec<c) threec=c;
            if ((v%5)==0) fivec=1;
            if ((v%7)==0) sevenc=1;
        }
        gmod = 1; while(twoc) { gmod*=2; twoc--; }
        while(threec) { gmod*=3; threec--; }
        if (fivec) gmod*=5; if (sevenc) gmod*=7; gmod *= 2;
        for (i=1; i<=n; i++) { scanf("%d", &v); room[i].q=v; }
        // check simple passable first
        for (i=0; i<=gmod; i++) stay[0][i]=stay[n+1][i]=1;
        for (i=1; i<=n; i++) {
            if (room[i].p==0) for (j=0; j<=gmod; j++) stay[i][j]=1;
            else {
                j=0; if (room[i].q>room[i].p) for (;j<room[i].q-room[i].p; j++) stay[i][j]=0;
                for (; j<room[i].q; j++) stay[i][j]=1;
                while(1) {
                    for (k=0; k<room[i].p; k++) { if (j>gmod) break; stay[i][j++]=0; } if (j>gmod) break;
                    for (k=0; k<room[i].p; k++) { if (j>gmod) break; stay[i][j++]=1; } if (j>gmod) break;
                }
            }
        }
        for (i=0; i<=n+1; i++) memset(dp[i], 0xff, (gmod+1)*sizeof(dp[i][0]));
        gn = n;
        i = dfs(0, 0);
        if (i<0) i=0;
        printf("%d\n", i);
    }
    return 0;
}
