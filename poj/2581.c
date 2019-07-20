#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cs[4];
int ss[504][4];
int vs[4] = {25, 10, 5, 1};
short dp[504][4];
int dfs(int c, int s) {
    if (s==3) {
        if (c<=cs[3]) return c;
        return -2;
    }
    if (dp[c][s]!=-1) return dp[c][s];
    int i; i=c/vs[s]; if (i>cs[s]) i=cs[s];
    int r=-1, t, ri;
    for (; i>=0; i--) {
        t = dfs(c-i*vs[s], s+1);
        if (t<0) continue;
        t += i;
        if (r<0 || r>t) { r=t;  ri=i; }
    }
    dp[c][s] = r;
    ss[c][s] = ri;
    return r;
}
int main() {
    char ts[8];
    int a, b, i;
    while( scanf("%s %d %d %d %d", ts, &cs[0], &cs[1], &cs[2], &cs[3]) == 5) {
        a=0;  i=0; while(ts[i]!='.'&&ts[i]!=0) { a=a*10+ts[i]-'0'; i++;}
        b=0; if (ts[i]) { i++; while(ts[i]!=0) { b=b*10+ts[i]-'0'; i++; } }
        a = a*100+b;
        memset(dp, 0xff, sizeof(dp));
        i = dfs(a, 0);
        if (i<0) printf("NO EXACT CHANGE\n");
        else {
            i = ss[a][0]; printf("%d", i);
            a -= vs[0]*i; i=ss[a][1]; printf(" %d", i);
            a -= vs[1]*i; i=ss[a][2]; printf(" %d", i);
            a -= vs[2]*i; printf(" %d\n", a);
        }
    }
    return 0;
}


