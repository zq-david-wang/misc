#include<stdio.h>

char map[1000][128];
char flag[1000][128];
char step[4][2]={
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};
int queue[1000*128];
int main() {
    int w, h, i, j;
    int mc, ci, cj, ni, nj, d, v;
    int head, tail;
    scanf("%d %d", &w, &h);
    for (i=0; i<h; i++) scanf("%s", map[i]);
    for (i=0; i<h; i++) for (j=0; j<w; j++) flag[i][j] = 0;
    mc = 0;
    for (i=0; i<h; i++) for (j=0; j<w; j++) {
        if (flag[i][j]) continue;
        if (map[i][j]=='.') continue;
        head=tail = 0;
        queue[head++] = (i<<16) | j;
        flag[i][j] = 1;
        while(tail<head) {
            v = queue[tail++];
            ci = v>>16;
            cj = v&0xffff;
            for (d=0; d<4; d++) {
                ni = ci+step[d][0];
                nj = cj+step[d][1];
                if (ni<0 || ni>=h || nj<0 || nj>=w) continue;
                if (flag[ni][nj]) continue;
                if (map[ni][nj]=='.') continue;
                flag[ni][nj]=1;
                queue[head++] = (ni<<16) | nj;
            }
        }
        if (mc<head) mc = head;
    }
    printf("%d\n", mc); 
    return 0;
}
