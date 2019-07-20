#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char tmap[64][64];
char flag[64][64][4];
char step[][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};
int main() {
    int tc, ti, n, r, i, x, y;
    int nx, ny, d;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        memset(tmap, 0, sizeof(tmap));
        scanf("%d %d", &n, &r);
        for (i=0; i<r; i++) {
            scanf("%d %d", &x, &y);
            tmap[x][y]=1;
        }
        scanf("%d %d", &x, &y);
        if (y==0) d=0;
        else if (x==0)d=1;
        else if (y==n+1) d=2;
        else d=3;
        memset(flag, 0, sizeof(flag));
        flag[x][y][d]=1;
        while(1) {
            nx = step[d][0]+x;
            ny = step[d][1]+y;
            if (nx==0||nx==n+1||ny==0||ny==n+1) {
                printf("%d %d\n", nx, ny);
                break;
            }
            if (tmap[nx][ny]) d=(d+1)%4;
            if (flag[nx][ny][d]==1) {
                printf("0 0\n");
                break;
            }
            flag[nx][ny][d]==1;
            x = nx; y=ny;
        }
    }
    return 0;
}


