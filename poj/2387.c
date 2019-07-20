#include<stdio.h>

#define INF 0x7fffffff

int map[1001][1001];
int dis[1001];
char flag[1001];
int main() {
    int t, n, i, j;
    int a, b, d;
    scanf("%d %d", &t, &n);
    for (i=1; i<=n; i++) for (j=1; j<=n; j++) map[i][j] = INF;
    for (i=0; i<t; i++) {
        scanf("%d %d %d", &a, &b, &d);
        if (map[a][b]>d) {
            map[a][b] = map[b][a] = d;
        }
    }
    for (i=1; i<=n; i++) {
        flag[i] = 0;
        dis[i] = INF;
    }
    dis[n] = 0;
    while(1) {
        d = INF;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (d>dis[i]) {
                d = dis[i];
                j = i;
            }
        }
        if (j==1) break;
        if (d==INF) break;
        flag[j] = 1;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (map[j][i]==INF)continue;
            if (dis[j]+map[j][i]<dis[i]) dis[i] = dis[j]+map[j][i];
        }
    }
    printf("%d\n", dis[1]);
    return 0;
}
