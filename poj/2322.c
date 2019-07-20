#include<stdio.h>

char map[16][16];
int cs[16];
int next[16][16];
int csi[16][20];
char dfs(int r, int c) {
    if (r==9&&c==9) return 1;
    int i, j, pi; for (i=r+1; i<10; i++) {
        if (map[i][c]!='*') continue;
        for (j=i-r; j<10; j++) {
            if (cs[j] && j+r<10 && map[r+j][c]=='*') {
                cs[j]--;
                pi = csi[j][cs[j]];
                next[r][c] = (pi<<24) |(j<<16) | (i<<8) | c;
                if (dfs(i, c)) return 1;
                cs[j]++;
            }
        }
    }
    for (i=c+1; i<10; i++) {
        if (map[r][i]!='*') continue;
        for (j=i-c; j<10; j++) {
            if (cs[j] && j+c<10 && map[r][j+c]=='*') {
                cs[j]--;
                pi = csi[j][cs[j]];
                next[r][c] = (pi<<24) | (j<<16) | (r<<8) | i;
                if (dfs(r, i)) return 1;
                cs[j]++;
            }
        }
    }
    return 0;
}
int main() {
    int i, n, l;
    int r, c;
    int nr, nc, pr, pc, v;
    for (i=0; i<10; i++) scanf("%s", map[i]);
    while(scanf("%d", &n)==1) {
        for (i=1; i<10; i++) cs[i]=0;
        for (i=0; i<n; i++) {
            scanf("%d", &l);
            if (l<=9) csi[l][cs[l]++] = i+1;
        }
        if (dfs(0, 0)) {
            r=0; c=0;
            while(r!=9||c!=9) {
                v = next[r][c];
                i = v>>24; l = (v>>16)&0xff; nr = (v>>8)&0xff; nc = v&0xff;
                pr = r; pc = c;
                if (nr==r) pc+=l;
                else pr+=l;
                printf("place plank %d to stump (%d,%d)\n", i, pr+1, pc+1);
                r = nr; c=nc;
            }
        } else printf("no solution possible\n");
        printf("\n");
    }
    return 0;
}
