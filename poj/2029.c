#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[128][128];
int cs[128];
int findmax(int s, int n) {
    int cc=0, mc=0;
    int i; for (i=0; i<s-1; i++) cc+=cs[i];
    for (; i<n; i++) {
        cc += cs[i]; if (mc<cc) mc=cc;
        cc -= cs[i-s+1];
    }
    return mc;
}
int main() {
    int n, w, h, i, s, t, x, y, m, cm, j;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        scanf("%d %d", &w, &h);
        memset(map, 0, sizeof(map));
        for (i=0; i<n; i++) {
            scanf("%d %d", &x, &y);
            x--; y--;
            map[x][y]=1;
        }
        scanf("%d %d", &s, &t);
        for (i=0; i<h; i++) cs[i]=0;
        for (i=0; i<s-1; i++) {
            for (j=0; j<h; j++) cs[j]+=map[i][j];
        }
        m=0;
        for (; i<w; i++) {
            for (j =0; j<h; j++) cs[j]+=map[i][j];
            cm = findmax(t, h);
            if (m<cm) m=cm;
            for (j =0; j<h; j++) cs[j]-=map[i-s+1][j];
        }
        printf("%d\n", m);
    }
    return 0;
}


