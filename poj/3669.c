#include<stdio.h>
#include<string.h>

short tl[302][302];
int queue[301*301];
char flag[302][302];
#define INF 2000
int main() {
    int i, v, m, j;
    int x, y, t;
    scanf("%d", &m);
    for (i=0; i<=301; i++) for (j=0; j<=301; j++) {
        tl[i][j] = INF;
        flag[i][j] = 0;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &x, &y, &t);
        if (tl[x][y]>t) tl[x][y]=t;
        if (x>0&&tl[x-1][y]>t) tl[x-1][y]=t;
        if (x<301&&tl[x+1][y]>t) tl[x+1][y]=t;
        if (y>0&&tl[x][y-1]>t) tl[x][y-1]=t;
        if (y<301&&tl[x][y+1]>t) tl[x][y+1]=t;
    }
    int head=0, tail=0;
    flag[0][0] = 1;
    if (tl[0][0]>0) queue[head++] = 0;
    x = 0; y = 0;
    while(tail<head) {
        v = queue[tail++];
        x = (v>>10)&0x3ff;
        y = v&0x3ff;
        t = v>>20;
        // printf("processing %d,%d %d %d\n", x, y, t, tl[x][y]);
        if (tl[x][y]==INF) break;
        t++;
        if (x>0&&flag[x-1][y]==0&&tl[x-1][y]>t) {
            if (tl[x-1][y]==INF) { x--; break; }
            flag[x-1][y] = 1;
            queue[head++] = (t<<20)|((x-1)<<10)|y;
        }
        if (x<301&&flag[x+1][y]==0&&tl[x+1][y]>t) {
            if (tl[x+1][y]==INF) { x++; break; }
            flag[x+1][y] = 1;
            queue[head++] = (t<<20)|((x+1)<<10)|y;
        }
        if (y>0&&flag[x][y-1]==0&&tl[x][y-1]>t) {
            if (tl[x][y-1]==INF) { y--; break; }
            flag[x][y-1] = 1;
            queue[head++] = (t<<20)|(x<<10)|(y-1);
        }
        if (y<301&&flag[x][y+1]==0&&tl[x][y+1]>t) {
            if (tl[x][y+1]==INF) { y++; break; }
            flag[x][y+1] = 1;
            queue[head++] = (t<<20)|(x<<10)|(y+1);
        }
    }
    if (tl[x][y]==INF) printf("%d\n", t);
    else printf("-1\n");
    return 0;
}
