#include<stdio.h>

char rwall[8][8], cwall[8][8];
int queue[256];
char dir[8][8];
char flag[8][8];
char rb[128];
int main() {
    int rs, cs, re, ce;
    int i, j, k, r, c;
    int r1, c1, r2, c2, t;
    int head, tail;
    while(1) {
        scanf("%d %d", &cs, &rs);
        if (cs==0) break;
        cs--; rs--;
        scanf("%d %d", &ce, &re);
        ce--; re--;
        for (i=0;i<8;i++) for (j=0;j<8;j++)cwall[i][j]=rwall[i][j]=flag[i][j]=0;
        for (k=0; k<3; k++) {
            scanf("%d %d %d %d", &c1, &r1, &c2, &r2);
            if (r1==r2) {
                if (c1>c2) {t=c1; c1=c2; c2=t;}
                for (i=c1; i<c2; i++) rwall[r1][i]=1;
            } else {
                if (r1>r2) {t=r1; r1=r2; r2=t;}
                for (i=r1; i<r2; i++) cwall[i][c1]=1;
            }
        }
        head=tail=0;
        queue[head++] = (rs<<8) | cs;
        flag[rs][cs] = 1;
        // printf("start with %d,%d\n", rs, cs);
        while(tail<head) {
            i=queue[tail++];
            r = i>>8; c=i&0xff;
            // printf("processing %d,%d\n", r,c);
            if (r==re&&c==ce) break;
            if (r>0&&flag[r-1][c]==0&&rwall[r][c]==0) {
                flag[r-1][c]=1; dir[r-1][c]='N';
                queue[head++] = ((r-1)<<8) | c;
            }
            if (r<5&&flag[r+1][c]==0&&rwall[r+1][c]==0) {
                flag[r+1][c]=1; dir[r+1][c]='S';
                queue[head++] = ((r+1)<<8) | c;
            }
            if (c>0&&flag[r][c-1]==0&&cwall[r][c]==0) {
                flag[r][c-1]=1; dir[r][c-1]='W';
                queue[head++] = (r<<8) | (c-1);
            }
            if (c<5&&flag[r][c+1]==0&&cwall[r][c+1]==0) {
                flag[r][c+1]=1; dir[r][c+1]='E';
                queue[head++] = (r<<8) | (c+1);
            }
        }
        // printf("process done with %d,%d\n" ,r ,c);
        i=128; rb[i]=0; r=re; c=ce;
        while(1) {
            if (r==rs&&c==cs) break;
            rb[--i]=dir[r][c];
            if (dir[r][c]=='N')r++;
            else if (dir[r][c]=='S') r--;
            else if (dir[r][c]=='E') c--;
            else c++;
        }
        printf("%s\n", rb+i);
    }
    return 0;
}
