#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[100][100];
char dpc[70][70];
char dpr[70][70][80];
void dfs(int r, int c, int h, int w) {
    if (dpc[r][c]!=-1) return;
    int i, nr, nc, cc=0;
    if (r+1<h&&map[r+1][c]>='0'&&map[r+1][c]<='9') {
        dfs(r+1, c, h, w);
        cc = dpc[r+1][c];
        nr = r+1; nc=c;
    }
    if (c+1<w&&map[r][c+1]>='0'&&map[r][c+1]<='9') {
        dfs(r, c+1, h, w);
        if (cc<dpc[r][c+1]) {
            cc = dpc[r][c+1]; nr=r; nc=c+1;
        } else if (cc==dpc[r][c+1]) {
            for (i=0; i<cc; i++) if (dpr[nr][nc][i]!=dpr[r][c+1][i]) break;
            if (i<cc&&dpr[nr][nc][i]<dpr[r][c+1][i]) {
                nr=r; nc=c+1;
            }
        }
    }
    cc++; dpr[r][c][0]=map[r][c];
    for (i=1; i<cc; i++) dpr[r][c][i]=dpr[nr][nc][i-1];
    dpr[r][c][i]=0;
    dpc[r][c] = cc;
}
int main() {
    int w, h, i, j, ml, k;
    char *r;
    while(1) {
        scanf("%d %d", &w, &h); if (w==0&&h==0) break;
        memset(dpc, 0xff, sizeof(dpc));
        for (i=0; i<h; i++) scanf("%s", map[i]);
        ml=-1;
        for (i=0; i<h; i++) for (j=0; j<w; j++) {
            if (map[i][j]<'1'||map[i][j]>'9') continue;
            dfs(i, j, h, w);
            if (ml<dpc[i][j]) { ml=dpc[i][j]; r=dpr[i][j]; }
            else if (ml==dpc[i][j]) {
                for(k=0; k<ml; k++) if (r[k]!=dpr[i][j][k]) break;
                if (k<ml&&r[k]<dpr[i][j][k]) r=dpr[i][j];
            }
        }
        printf("%s\n", r);
    }
    return 0;
}


