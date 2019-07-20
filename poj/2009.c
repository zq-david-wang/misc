#include<stdio.h>

struct {
    unsigned int m, cap;
    short c, cc, dp;
    short cs[1024];
}ms[1024];
int ccc[31][30];
void build() {
    int i, j;
    for (j=1; j<=30; j++) { 
        ccc[j][0] = 1; ccc[j][1] = j;
        ccc[j][j] = 1;
        ccc[0][j] = 0;
    }
    for (i=1; i<=30; i++) {
        for (j=2; j<i; j++) {
            ccc[i][j] = ccc[i-1][j]+ccc[i-1][j-1];
            if (ccc[i][j]>1024) ccc[i][j] = 1024;
        }
    }
}

int count(int s) {
    if (ms[s].dp != -1) return ms[s].dp;
    int c = 0;
    int i; for(i=0; i<ms[s].cc; i++) {
        c += count(ms[s].cs[i]);
    }
    c = ms[s].cap-c;
    if (c>ms[s].c) c = ms[s].c;
    ms[s].dp = c;
    return c;
}
int main() {
    int c, t, k, i, j, p;
    int n, cn=0, rc = 0;
    unsigned int m;
    build();
    scanf("%d %d %d", &c, &t, &k);
    for (i=0; i<c; i++) {
        scanf("%d", &n);
        m = 0;
        for (j=0; j<n; j++) {
            scanf("%d", &p);
            m |= (1<<p);
        }
        if (n<k) continue;
        if (ccc[n][k] >= c) { rc++; continue; }
        for (j=0; j<cn; j++) if (ms[j].m==m) break;
        if (j<cn) { ms[j].c++; }
        else {
            ms[cn].m = m;
            ms[cn].c = 1;
            ms[cn].cc = 0;
            ms[cn].cap = ccc[n][k];
            ms[cn].dp = -1;
            cn++;
        }
    }
    for (i=0; i<cn; i++) {
        for (j=0; j<cn; j++) {
            if (ms[j].m == ms[i].m) continue;
            if ((ms[j].m & ms[i].m) == ms[j].m) {
                ms[i].cs[ms[i].cc++] = j;
            }
        }
    }
    for (i=0; i<cn; i++) rc += count(i);
    printf("%d\n", rc);
    return 0;
}
