#include<stdio.h>

char map[101][101];
char flag[101][101];
int queue[10000];
int main() {
    int n, m, k, i, j, v;
    int r, c, rc = 0;
    int head, tail;
    scanf("%d %d %d", &n, &m, &k);
    for (i=1; i<=n; i++) for (j=1; j<=m; j++) {
        map[i][j] = 0;
        flag[i][j] = 0;
    }
    for (i=0; i<k; i++) {
        scanf("%d %d", &r, &c);
        map[r][c] = 1;
    }
    for (i=1; i<=n; i++) for (j=1; j<=m; j++) {
        if (map[i][j]==0) continue;
        if (flag[i][j]) continue;
        head = tail = 0;
        queue[head++] = (i<<16)|j;
        flag[i][j] = 1;
        while(tail<head) {
            v = queue[tail++];
            r = v>>16; c = v&0xffff;
            if (r-1>=1&&map[r-1][c]&&flag[r-1][c]==0) { flag[r-1][c]=1; queue[head++]=((r-1)<<16)|c; }
            if (r+1<=n&&map[r+1][c]&&flag[r+1][c]==0) { flag[r+1][c]=1; queue[head++]=((r+1)<<16)|c; }
            if (c-1>=1&&map[r][c-1]&&flag[r][c-1]==0) { flag[r][c-1]=1; queue[head++]=(r<<16)|(c-1); }
            if (c+1<=m&&map[r][c+1]&&flag[r][c+1]==0) { flag[r][c+1]=1; queue[head++]=(r<<16)|(c+1); }
        }
        if (rc<head) rc = head;
    }
    printf("%d\n", rc);
    return 0;
}
