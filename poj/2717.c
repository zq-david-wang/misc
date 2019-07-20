#include<stdio.h>
#include<string.h>

int gcd(int a, int b)
{
    int t; while(a) { t=a; a=b%a; b=t; }
    return b;
}

short dp[2][200][2000];
char choice[2][200][2000];
int gm, gn;
int dfs(int n, int x ,int t) {
    if (x==t) return 0;
    if (t==0) return 0;
    if (t<0) return -2;
    if (dp[n][x][t] !=-1) return dp[n][x][t];
    dp[n][x][t]=-2;
    int r=-2, tr;
    char s=0;
    // do not flip
    if (x) {tr=dfs(0, 0, t-x); if (tr>=0) { if (r<0||r>tr) { r=tr; s=0; } } }
    // tr=dfs(0, gn, t-x); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=1; } }
    // tr=dfs(1, gm, t-x); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=0; }}
    // tr=dfs(0, gn-gm, t-x-gm); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=2;} }
    if (1) {
        if (n==0) {
            if (gm<x) {
                tr=dfs(0, x-gm, t-gm); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+0;} }
            } else {
                tr=dfs(1, gm-x, t-x); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+0;} }
            }
            tr=dfs(0, gn-x, t); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+1; }}
            if (gm<gn-x) {
                tr=dfs(0, gn-x-gm, t-gm); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+2; } }
            } else {
                tr=dfs(1, gm-(gn-x), t-(gn-x)); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+2; }}
            }
        } else {
            tr=dfs(0, gn-x, t-x); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+1;}}
            tr=dfs(1, gm-x, t); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+0; }}
            tr=dfs(0, gn-(gm-x), t-(gm-x)); if (tr>=0) { tr++; if (r<0||r>tr) { r=tr; s=8+2;} }
        }
    }
    // printf("dfs %d,%d,%d ==> %d\n", n, x, t, r);
    dp[n][x][t]=r;
    choice[n][x][t]=s;
    return r;
}
int main() {
    int m, n, t, g;
    int r, s, tn, tc, tt, ct;
    while(1) {
        scanf("%d %d %d", &m, &n, &t); if (m==0) break;
        g = gcd(m, n);
        if (t%g) printf("Impossible\n");
        else {
            memset(dp, 0xff, sizeof(dp));
            gm=m; gn=n;
            r = dfs(0, n-m, t-m);
            if (r>=0) { 
                printf("0: %d,%d\n", m, n);
                tn=0; tc=n-m; tt=t-m; ct=m;
                while(tt) {
                    s = choice[tn][tc][tt];
                    if (s==0) { ct+=tc; tt-=tc; tn=0; tc=0; }
                    else if (s==8) {
                        printf("%d: %d\n", ct, m);
                        if (tn==0) {
                            if (m<tc) { ct+=m; tt-=m; tc=tc-m; }
                            else { ct+=tc; tt-=tc; tn=1; tc=m-tc; }
                        } else { tc=m-tc; }
                    } else if(s==9) {
                        printf("%d: %d\n", ct, n);
                        if (tn==1) {
                            ct+=tc; tt-=tc; tn=0; tc=n-tc;
                        } else { tc=n-tc; }
                    } else {
                        printf("%d: %d,%d\n", ct, m, n);
                        if (tn==0) {
                            if (m<(n-tc)) { ct+=m; tt-=m; tc=(n-tc)-m; }
                            else { ct+=(n-tc); tt-=(n-tc); tn=1; tc=m-(n-tc); }
                        } else {
                            ct+=(m-tc); tt-=(m-tc); tn=0; tc=n-(m-tc);
                        }
                    }
                }
            } else printf("Impossible\n");
        }
        printf("----------\n");
    }
    return 0;
}
