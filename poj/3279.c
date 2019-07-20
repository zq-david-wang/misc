#include<stdio.h>

char map[16][16];
char cs[16][16];
char prow[16];
char rs[16][16];
char srs[16][16];
int main() {
    int m, n, i, j, v, k;
    scanf("%d %d", &m, &n);
    for (i=0; i<m; i++) for (j=0; j<n; j++) {
        scanf("%d", &v); map[i][j] = v;
    }
    int max = (1<<n)-1;
    int c, mc=256;
    for (i=0; i<=max; i++) {
        c = 0;
        for (j=0; j<m; j++) for(k=0; k<n; k++) cs[j][k] = 0;
        for (j=0; j<n; j++) {
            rs[0][j] = 0;
            if ((1<<(n-1-j))&i) {
                // flip 0, j;
                c++;
                cs[0][j]++;
                if (j>0) cs[0][j-1]++;
                if (j<n-1) cs[0][j+1]++;
                cs[1][j]++;
                rs[0][j] = 1;
            }
        }
        for (j=0; j<n; j++) prow[j] = (map[0][j]+cs[0][j])&1;
        for (j=1; j<m; j++) {
            if (c>=mc) break;
            for (k=0; k<n; k++) {
                rs[j][k] = 0;
                if (prow[k]) {
                    //flip i, j
                    cs[j][k]++;
                    c++;
                    if (k>0) cs[j][k-1]++;
                    if (k<n-1) cs[j][k+1]++;
                    cs[j+1][k]++;
                    rs[j][k] = 1;
                }
            } 
            for (k=0; k<n; k++) prow[k] = (map[j][k]+cs[j][k])&1;
        }
        if (j<m) continue;
        for (k=0; k<n; k++) if (prow[k]) break;
        if (k==n) {
            if (mc>c) {
                mc = c;
                // copy result
                for (j=0;j<m;j++) for(k=0; k<n; k++) srs[j][k] = rs[j][k];
            }
        }
    }
    if (mc==256) printf("IMPOSSIBLE\n");
    else {
        for (j=0; j<m; j++) {
            for (k=0; k<n; k++) {
                if (k==0) printf("%d", srs[j][k]);
                else printf(" %d", srs[j][k]);
            }
            printf("\n");
        }
    }
    return 0;
}
