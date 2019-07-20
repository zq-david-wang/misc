#include<stdio.h>

char map[1000][1000];
unsigned queue[1000*1000*2];
int depth[1000][1000];
char token[1000][1000];
char step[4][2]={
    {1, 0}, {-1,0}, {0, 1}, {0,-1}
};
int main() {
    int w, h, i, j, si, sj, m, ni, nj, days;
    char d;
    scanf("%d %d", &w, &h);
    for (i=0; i<h; i++) for (j=0; j<w; j++) {
        scanf("%d", &m);
        map[i][j] = m;
        if (m==2) { si = i; sj = j; }
    }
    int head=0, tail=0;
    queue[head++] = (si<<16) | sj;
    map[si][sj] = 5; depth[si][sj] = 0; token[si][sj] = 0;
    days = -1;
    while(tail<head) {
        m = queue[tail++];
        i = m>>16;
        j = m&0xffff;
        for (d=0; d<4; d++) {
            ni = i+step[d][0];
            nj = j+step[d][1];
            if (ni<0 || ni>=h || nj<0 || nj>=w) continue;
            if (map[ni][nj]==1) continue;
            if (map[ni][nj]==6) continue;
            if (map[ni][nj]==3 && token[i][j]==1) {
                days = depth[i][j]+1;
                break;
            }
            if (map[ni][nj]==3) continue;
            if (map[ni][nj]==5 && token[i][j]==0) continue;
            if (token[i][j]==1) {
                token[ni][nj] = 1;
                depth[ni][nj] = depth[i][j]+1;
                map[ni][nj] = 6;
                queue[head++] = (ni<<16)|nj;
            } else {
                depth[ni][nj] = depth[i][j]+1;
                token[ni][nj] = token[i][j];
                if (map[ni][nj] == 4) {
                    token[ni][nj] = 1;
                    map[ni][nj] = 6;
                } else map[ni][nj] = 5;
                queue[head++] = (ni<<16)|nj;
            }
        }
        if (days>=0) break;
    }
    printf("%d\n", days);
    return 0;
}
