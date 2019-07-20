/*
 * =====================================================================================
 *
 *       Filename:  3642.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月20日 16时12分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#define INF 0x7fffffff
int map[32][32];

int dis0[32], disn[32];
char flag[32];

void dij(int* d, int s, int n) {
    int i;
    for (i=0; i<=n+1; i++) {
        d[i] = INF;
        flag[i] = 0;
    }
    d[s] = 0;
    int mdi, md;
    while(1) {
        md = INF;
        for (i=0; i<=n+1; i++) {
            if (flag[i]==1) continue;
            if (d[i]<md) { 
                md = d[i];
                mdi = i;
            }
        }
        if (md == INF) break;
        flag[mdi] =1;
        for (i=0; i<=n+1; i++) {
            if (flag[i]==1) continue;
            if (map[mdi][i]<0) continue;
            if (map[mdi][i] + d[mdi] < d[i]) d[i] = map[mdi][i]+d[mdi];
        }
    }
}
int main() {
    int n, m, i, j;
    int a, b, d;
    scanf("%d %d", &n, &m);
    for (i=0; i<=n+1; i++) for(j=0; j<=n+1; j++) map[i][j] = -1;
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &d);
        map[a][b] = map[b][a] = d;
    }
    dij(dis0, 0, n);
    dij(disn, n+1, n);
    d = INF;
    for (i=1; i<=n; i++) {
        a = dis0[i]+disn[i]+5;
        if (d>a)d = a;
    }
    printf("%d\n", d);
    return 0;
}
