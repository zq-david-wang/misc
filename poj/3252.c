#include<stdio.h>
#include<string.h>

int dp[32][32][32];
int dfs(int b, int zc, int oc) {
    if (b==0) {
        if (zc>=oc) return 1;
        return 0;
    }
    if (dp[b][zc][oc] != -1) return dp[b][zc][oc];
    int r = dfs(b-1, zc+1, oc) + dfs(b-1, zc, oc+1);
    dp[b][zc][oc] = r;
    // printf("dp %d,%d,%d == > %d\n", b, zc, oc, r);
    return r;
}

int count(int v) {
    if (v==0) return 1;
    int t = v;
    int bc = 0; while(t) {
        bc++;
        t /= 2;
    }
    int c = 1, i;
    for (i=bc-2; i>=0; i--) {
        c += dfs(i, 0, 1);
    }
    int oc = 1, zc = 0;
    for (i=bc-2; i>=0; i--) {
        if (v & (1<<i)) {
            c += dfs(i, zc+1, oc);
            oc++;
        } else zc++;
    }
    c += (zc>=oc);
    // printf("count for %d is %d\n", v, c);
    return c;
}

int main() {
    int s, f, c1, c2;;
    scanf("%d %d", &s, &f);
    memset(dp, 0xff, sizeof(dp));
    c1 = count(s-1);
    c2 = count(f);
    c2 -= c1;
    printf("%d\n", c2);
    return 0;
}
