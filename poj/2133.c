#include<stdio.h>
#include<string.h>

char buf[32];
int convert(int n) {
    int v = 0;
    int i;for (i=0; i<n; i++) {
        v = v*2+buf[i]-'0';
    }
    return v;
}
int count1s(int v) {
    int c = 0;
    while(v) {
        c++;
        v = v&(v-1);
    }
    return c;
}
int ntags[65536];
int candi[65536];
char flag[65536];
char dflag[65536];
int tags[128];

int dp[65536][100];
int gn;
int dfs(int v, int s, int m) {
    if (s==gn) return -2;
    if (dp[v][s]!=-1) return dp[v][s];
    int r = -2, t;
    if (v==tags[s]) return 1;
    t = dfs(v, s+1, m);
    if (t>=0) { if (r<0||r>t)r=t; }
    t = dfs(((v^tags[s])&m), s+1, m);
    if (t>=0) { t++; if (r<0||r>t)r=t; }
    dp[v][s] = r;
    return r;
}
int main() {
    int b, e, i, goal, v, c=0, nv, j, cc;
    int zex = 0;
    scanf("%d %d", &b, &e);
    scanf("%s", buf);
    goal = convert(b);
    int max=1; for (i=0; i<b; i++) max*=2;
    int mask = max-1;
    memset(flag, 0, sizeof(flag));
    memset(dflag, 0, sizeof(dflag));
    for (i=0; i<e; i++) {
        scanf("%s", buf);
        v = convert(b);
        if (v==0) zex=1;
        tags[i] = v;
        if (flag[v]==0) {
            ntags[c++] = v;
            flag[v] = 1;
        }
        cc = c;
        for (j=0; j<cc; j++) {
            nv = (v^ntags[j])&mask;
            if (flag[nv]==0) {
                ntags[c++] = nv;
                flag[nv] = 1;
            }
        }
    }
    for (i=0; i<e; i++) for (j=0; j<e; j++) dflag[(tags[i]^tags[j])&mask]=1;
    int md=32, d, dc=0;
    for (i=0; i<c; i++) {
        v = ntags[i];
        d = count1s((v^goal)&mask);
        if (md>d) { dc=0; md=d;}
        if (md==d) candi[dc++] = v;
    }
    md = 0x7fffffff;
    memset(dp, 0xff, sizeof(dp));
    gn = e;
    for (i=0; i<dc; i++) {
        if (candi[i]==0) d = 2;
        else {
            d = dfs(candi[i], 0, mask);
            // printf("dfs for %d is %d  dflag %d flag 0 is %d\n", candi[i], d, dflag[candi[i]], flag[0]);
            if (d==1) {
                if (dflag[candi[i]])d=2;
                else {
                    if (zex==1)d=2;
                    else d=3;
                }
            }
        }
        if (d>0 && (md>d || (md==d&&candi[i]<v))) {
            md = d;
            v = candi[i];
        }
    }
    for (i=0; i<b; i++) buf[i] = ((v>>(b-i-1))&1)+'0';
    buf[b] = 0;
    printf("%d\n%s\n", md-1, buf);
    return 0;
}
