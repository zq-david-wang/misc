#include<stdio.h>


#define INF 0xffffff
int dis[500];
int map[500][500];
char flag[500];
int main() {
    int c, i, n, j, k;
    int ld, md, mi;
    scanf("%d", &c);
    for (i=0; i<c; i++) {
        scanf("%d", &n);
        for (j=0; j<n; j++) for (k=0; k<n; k++) scanf("%d", &map[j][k]);
        for (j=0; j<n; j++) {
            dis[j] = INF;
            flag[j] = 0;
        }
        dis[0] = 0;
        ld = 0;
        while(1) {
            md = INF;
            for (j=0; j<n; j++) {
                if (flag[j]) continue;
                if (dis[j]<md) {
                    md = dis[j];
                    mi = j;
                }
            }
            if (md==INF) break;
            if (ld<md) ld = md;
            flag[mi] = 1;
            for (j=0; j<n; j++) {
                if (flag[j]) continue;
                if (dis[j] > map[j][mi]) dis[j] = map[j][mi];
            }
        }
        printf("%d\n", ld);
    }
    return 0;
}
