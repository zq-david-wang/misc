#include<stdio.h>

int map[1001][1001];
char flag[1001];
int md[1001];
int main() {
    int n, m, i, a, b, w, mi, j;
    int c;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) for (j=1;j<=n;j++)map[i][j]=-1;
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &w);
        if (map[a][b]<w) {
            map[a][b]=w;
            map[b][a]=w;
        }
    }
    for (i=1; i<=n; i++) {md[i] = -1; flag[i]=0;}
    md[1] = 0;
    c = 0;
    for (i=0; i<n; i++) {
        m = -1;
        for (j=1; j<=n; j++) {
            if (flag[j]) continue;
            if (m<md[j]) {
                m = md[j];
                mi = j;
            }
        }
        if (m==-1) break;
        c += m;
        flag[mi] = 1;
        for (j=1; j<=n; j++) {
            if (flag[j]) continue;
            if (map[mi][j]==-1) continue;
            if (map[mi][j]>md[j])md[j] = map[mi][j];
        }
    }
    if (i<n) printf("-1\n");
    else printf("%d\n", c);
    return 0;
}
