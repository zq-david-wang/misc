#include<stdio.h>
#include<string.h>

char map[301][301];
int mb[300];
int queue[301];
int nei[301][300];
int neic[301];
char flag[301];
int main() {
    int n, m, i, j, c;
    int a, b, i1, i2, v, d;
    scanf("%d %d", &n, &m);
    memset(map, 0, sizeof(map));
    for (i=0; i<m; i++) {
        scanf("%d", &c);
        for (j=0; j<c; j++) {
            scanf("%d", &mb[j]);
        }
        for (i1=0; i1<c; i1++) {
            a = mb[i1];
            for (i2=i1+1; i2<c; i2++) {
                b = mb[i2];
                map[a][b] = 1;
                map[b][a] = 1;
            }
        }
    }
    for (i=1; i<=n; i++) {
        neic[i] = 0;
        for (j=1; j<=n; j++) {
            if (map[i][j]) {
                nei[i][neic[i]++]=j;
            }
        }
    }
    int s, ms=0x7fffffff;
    int head, tail;
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) flag[j]=0;
        s = 0;
        head=tail=0;
        queue[head++] = i;
        flag[i] = 1;
        while(tail<head) {
            v = queue[tail++];
            a = v & 0xffff;
            d = v>>16;
            d++;
            for (i1=0; i1<neic[a]; i1++) {
                b = nei[a][i1];
                if (flag[b]==0) {
                    flag[b] = 1;
                    s += d;
                    queue[head++] = (d<<16)|b;
                }
            }
        }
        if (ms>s) ms=s;
    }
    double t = ms*100; t/=(n-1);
    i = t;
    printf("%d\n", i);
    return 0;
}
