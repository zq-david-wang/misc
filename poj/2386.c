#include<stdio.h>

char map[128][128];
char flag[128][128];
int queue[10000];
int dir[8][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {1, -1},
    {1, 1},
    {-1, 0},
    {-1, 1},
    {-1, -1},
};
int main() {
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; i++) scanf("%s", map[i]);
    for (i=0; i<n; i++) for (j=0; j<m; j++) flag[i][j] = 0;
    int h, t, c=0, d;
    int ci, cj, v, ni, nj;
    for (i=0; i<n; i++) for (j=0; j<m; j++) {
        if (map[i][j]=='.') continue;
        if (flag[i][j]) continue;
        c++;
        h = t = 0;
        flag[i][j] = 1;
        queue[h++] = (i<<8 | j);
        while(t<h) {
            v = queue[t++];
            ci = v>>8;
            cj = v&0xff;
            for (d=0; d<8; d++) {
                ni = ci+dir[d][0];
                nj = cj+dir[d][1];
                if (ni<0||ni>=n||nj<0||nj>=m) continue;
                if (map[ni][nj]=='.') continue;
                if (flag[ni][nj]) continue;
                flag[ni][nj] = 1;
                queue[h++] = (ni<<8|nj);
            }
        }
    }
    printf("%d\n", c);
    return 0;
}
