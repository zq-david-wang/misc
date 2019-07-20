#include<stdio.h>

char map[5][8];
char flag[5*5];
char qflag[5*5];
char path[8];
int gc;

char steps[4][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1}
};
int queue[32];

int verify() {
    int s = path[0];
    int head=0, tail=0;
    queue[head++] = s;
    qflag[s] = 1;
    int r, c, nr, nc, ns, d;
    while(tail<head) {
        s = queue[tail++];
        r = s/5; c = s%5;
        for (d=0; d<4; d++) {
            nr = r+steps[d][0];
            nc = c+steps[d][1];
            ns = nr*5+nc;
            if (nr<0||nr>=5||nc<0||nc>=5||flag[ns]==0||qflag[ns]==1) continue;
            qflag[ns] = 1;
            queue[head++] = ns;
        }
    }
    for (s=0; s<7; s++) qflag[path[s]] = 0;
    // printf("veirfy %d\n", head);
    // for (s=0; s<7; s++) printf("(%d,%d)", path[s]/5, path[s]%5);printf("\n");
    return head==7;
}
void dfs(int s, int si, int c1, int c2) {
    if (c2>3) return;
    if (si==7) { 
        if (verify()) gc++;
        return;
    }
    int n, r, c, ii, i;
    n = 5;
    if (si==0) n = 19;
    for (i=0; i<n;i++) {
        ii = s+i;
        if (ii>=25) break;
        r = ii/5; c = ii%5;
        flag[ii] = 1;
        path[si] = ii;
        if (map[r][c]=='J') dfs(ii+1, si+1, c1+1, c2);
        else dfs(ii+1, si+1, c1, c2+1);
        flag[ii] = 0;
    }
}
int main() {
    int i; for (i=0; i<5; i++) scanf("%s", map[i]);
    gc = 0;
    for (i=0; i<25; i++) flag[i] = qflag[i] = 0;
    dfs(0, 0, 0, 0);
    printf("%d\n", gc);
    return 0;
}
