#include<stdio.h>
#include<string.h>

short path[32];
char steps[8][2] = {
    {-2, -1},
    {-2, 1},
    {-1, -2},
    {-1, 2},
    {1, -2},
    {1, 2},
    {2, -1},
    {2, 1},
};
#define SIZE 32
int gn, gr, gc;
char flag[SIZE][SIZE];

int dfs(int si, int sj, int c) {
    // printf("dfs %d %d (%d)\n", si, sj, c);
    if (c==gn) return 1;
    int k, ni, nj, v;
    for (k=0; k<8; k++) {
        ni = si+steps[k][0];
        nj = sj+steps[k][1];
        // printf("try %d,%d ()\n", ni, nj);
        if (ni<0||ni>=gr||nj<0||nj>=gc) continue;
        // printf("try %d,%d (%d)\n", ni, nj, flag[ni][nj]);
        if (flag[ni][nj]==1) continue;
        flag[ni][nj] = 1;
        path[c] = (ni<<8) | nj;
        v = dfs(ni, nj, c+1);
        flag[ni][nj] = 0;
        if (v) return 1;
    } 
    return 0;
}
int main() {
    int c, i, nr, nc, j, k, v;
    memset(flag, 0, sizeof(flag));
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        printf("Scenario #%d:\n", i);
        scanf("%d %d", &nc, &nr);
        gn = nr*nc;
        gr = nr; gc = nc;
        v = 0; for (j=0; j<nr; j++) {
            for (k=0; k<nc; k++) {
                path[0] = (j<<8) | k;
                flag[j][k] = 1;
                v = dfs(j, k, 1);
                flag[j][k] = 0;
                if (v) break;
            }
            if (v) break;
        }
        if (v==0) printf("impossible\n");
        else {
            for (j=0; j<gn; j++) {
                printf("%c%c", (path[j]>>8)+'A', (path[j]&0xff)+'1');
            } printf("\n");
        }
        printf("\n");
    }
    return 0;
}
