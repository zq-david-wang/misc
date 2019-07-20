#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[40][64];
struct { char r, c; } queue[1600];
short dis[40][40];
char steps[][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};
int main() {
    int ti, tc, w, h, j, i, si, sj, ei, ej;
    int c1, c2, c3;
    int ni, nj, d, nd, head, tail, k;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &w, &h);
        for (i=0; i<h; i++) { 
            scanf("%s", map[i]);
            for (j=0; j<w; j++) {
                if (map[i][j]=='S') { si=i; sj=j; map[i][j]='.';}
                if (map[i][j]=='E') { ei=i; ej=j; map[i][j]='.';}
            }
        }
        i=si; j=sj; d=0; c1=1;
        while(1) {
            if (i==ei&&j==ej) break;
            nd = (d+3)%4;
            ni = i+steps[nd][0];
            nj = j+steps[nd][1];
            if (ni<0||ni>=h||nj<0||nj>=w||map[ni][nj]=='#') {
                while(1) {
                    ni = i+steps[d][0];
                    nj = j+steps[d][1];
                    if (ni<0||ni>=h||nj<0||nj>=w||map[ni][nj]=='#') {
                        d++; d%=4;
                        continue;
                    }
                    break;
                }
            } else d=nd;
            i=ni; j=nj; c1++;
        }
        i=si; j=sj; d=0; c2=1;
        while(1) {
            if (i==ei&&j==ej) break;
            nd = (d+1)%4;
            ni = i+steps[nd][0];
            nj = j+steps[nd][1];
            if (ni<0||ni>=h||nj<0||nj>=w||map[ni][nj]=='#') {
                // if no right, try from up ahead
                while(1) {
                    ni = i+steps[d][0];
                    nj = j+steps[d][1];
                    if (ni<0||ni>=h||nj<0||nj>=w||map[ni][nj]=='#') {
                        d+=3; d%=4;
                        continue;
                    }
                    break;
                }
            } else d=nd;
            i=ni; j=nj; c2++;
        }
        memset(dis, 0xff, sizeof(dis));
        head=tail=0;
        queue[head].r=si; queue[head].c=sj; head++;
        dis[si][sj]=1;
        while(tail<head) {
            i=queue[tail].r; j=queue[tail].c; tail++;
            if (i==ei&&j==ej) break;
            for (k=0; k<4; k++) {
                ni = i+steps[k][0];
                nj = j+steps[k][1];
                if (ni<0||ni>=h||nj<0||nj>=w||map[ni][nj]=='#'||dis[ni][nj]!=-1) continue;
                dis[ni][nj] = dis[i][j]+1;
                queue[head].r = ni;
                queue[head].c = nj; head++;
            }
        }
        printf("%d %d %d\n", c1, c2, dis[ei][ej]);
    }
    return 0;
}


