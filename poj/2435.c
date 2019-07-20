#include<stdio.h>
#include<string.h>

char map[84][84];
char flag[84][84];
int path[84][84];
short stack[84*84][2];
int queue[84*84];
int main() {
    int n, e, i, j;
    int si, sj, ei, ej, v;
    scanf("%d %d", &n, &e);
    int tn = 2*n-1;
    int te = 2*e-1;
    for (i=0; i<tn; i++) {
        scanf("%s", map[i]);
        for (j=0; ;j++) {
            if (map[i][j]==0) break;
            if (map[i][j]=='S') { si = i; sj = j; }
            if (map[i][j]=='E') { ei = i; ej = j; }
        }
    }
    int head, tail;
    int ci, cj;
    head=tail=0;
    queue[head++] = (si<<16) | sj;
    memset(flag, 0, sizeof(flag));
    flag[si][sj] = 1;
    while(tail<head) {
        v = queue[tail++];
        ci = v>>16; cj = v&0xffff;
        if (ci==ei && cj==ej) break;
        for (i=ci+1; i<tn; i++) {
            if (map[i][cj]=='.' || map[i][cj]=='-' || flag[i][cj]==1) break;
            path[i][cj] = v;
            flag[i][cj] = 1;
            queue[head++] = (i<<16) | cj;
        }
        for (i=ci-1; i>=0; i--) {
            if (map[i][cj]=='.' || map[i][cj]=='-' || flag[i][cj]==1) break;
            path[i][cj] = v;
            flag[i][cj] = 1;
            queue[head++] = (i<<16) | cj;
        }
        for (j=cj+1; j<te; j++) {
            if (map[ci][j]=='.' || map[ci][j]=='|' || flag[ci][j]==1) break;
            path[ci][j] = v;
            flag[ci][j] = 1;
            queue[head++] = (ci<<16) | j;
        }
        for (j=cj-1; j>=0; j--) {
            if (map[ci][j]=='.' || map[ci][j]=='|' || flag[ci][j]==1) break;
            path[ci][j] = v;
            flag[ci][j] = 1;
            queue[head++] = (ci<<16) | j;
        }
    }
    i=0; ci=ei; cj=ej;
    while(1) {
        stack[i][0] = ci;
        stack[i][1] = cj; i++;
        v = path[ci][cj];
        ci = v>>16; cj=v&0xffff;
        if (ci==si && cj==sj) break;
    }
    int count = i;
    while(count>0) {
        count--;
        i = stack[count][0]; j = stack[count][1];
        // printf("%d,%d--> %d,%d\n", ci, cj, i, j);
        if (i==ci && j>cj) printf("E %d\n", (j-cj)/2);
        else if (i==ci && j<cj) printf("W %d\n", (cj-j)/2);
        else if (j==cj && i>ci) printf("S %d\n", (i-ci)/2);
        else printf("N %d\n", (ci-i)/2);
        ci = i; cj = j;
    }
    return 0;
}
