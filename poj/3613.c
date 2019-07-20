#include<stdio.h>

int ary1[1001], ary2[1001];
int ary3[1001], ary4[1001];
char flag[1001];
#define INF 0x7fffffff
int dis[20][100][100];
char used[1001];
int nodes[1001], nc, ids[1001];
int main() {
    int n, t, s, e, i, j;
    int a, b, d;
    int *dp, *dp1, *tp, *q1, *q2;
    int qc, nqc;
    int bits = 0;
    int i1, i2;
    scanf("%d %d %d %d", &n, &t, &s, &e);
    for (i=0; i<=1000; i++) used[i] = 0;
    a = n; while(a) { bits++; a>>=1; }
    nc = 0;
    for (i=0; i<100; i++) for (j=0; j<100; j++) dis[0][i][j] = INF;
    for (i=0; i<t; i++) {
        scanf("%d %d %d", &d, &a, &b);
        if (used[a]==0) { used[a] = 1; ids[a] = nc; nodes[nc++] = a; }
        if (used[b]==0) { used[b] = 1; ids[b] = nc; nodes[nc++] = b; }
        dis[0][ids[a]][ids[b]] = d;
        dis[0][ids[b]][ids[a]] = d;
    }
    for (i=1; i<bits; i++) {
        for (i1=0; i1<nc; i1++) for (i2=0; i2<nc; i2++) {
            dis[i][i1][i2] = INF;
            for (j=0; j<nc; j++) {
                if (dis[i-1][i1][j] == INF) continue;
                if (dis[i-1][j][i2] == INF) continue;
                a = dis[i-1][i1][j] + dis[i-1][j][i2];
                if (a<dis[i][i1][i2]) dis[i][i1][i2] = a;
            }
            // printf("%d: %d,%d  ==> %d\n", i, i1, i2, dis[i][i1][i2]);
        }
    }
    dp = ary1; dp1 = ary2;
    q1 = ary3; q2 = ary4;
    for (i=0; i<=100; i++) flag[i] = 0;
    s = ids[s]; e = ids[e];
    dp[e] = 0;
    q1[0] = e; qc = 1;
    for (i=bits-1; i>=0; i--) {
        if ((n&(1<<i))==0) continue;
        nqc = 0;
        for (j=0; j<qc; j++) {
            a = q1[j];
            for (b=0; b<nc; b++) {
                if (dis[i][a][b]==INF) continue;
                if (flag[b]==0) {
                    dp1[b] = dp[a]+dis[i][a][b];
                    q2[nqc++] = b;
                    flag[b] = 1;
                } else if (dp1[b]>(dp[a]+dis[i][a][b])) dp1[b] = dp[a]+dis[i][a][b];
            }
        }
        for (j=0; j<nqc; j++) flag[q2[j]] = 0;
        tp=dp; dp=dp1; dp1=tp;
        tp=q1; q1=q2; q2=tp;
        qc = nqc;
        // printf("bit %d:::", i); for (j=0; j<qc; j++) printf("%d ", q1[j]); printf("\n");
    }
    printf("%d\n", dp[s]);
    return 0;
}
