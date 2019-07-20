#include<stdio.h>
#include<math.h>

double dis[1000][1000];
int xs[1000], ys[1000];
double path[1000];
char flag[1000];
int main() {
    int n, m, i, j, a, b, mi;
    double x, y, r, md, d;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; i++) scanf("%d %d", &xs[i], &ys[i]);
    for (i=0; i<n; i++) {
        dis[i][i] = 0;
        for (j=i+1; j<n; j++) {
            x = xs[i]-xs[j];
            y = ys[i]-ys[j];
            d = sqrt(x*x+y*y);
            dis[i][j] = dis[j][i] = d;
        }
    }
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        dis[a][b] = 0;
        dis[b][a] = 0;
    }
    for (i=0; i<n; i++) {
        path[i] = -1;
        flag[i] = 0;
    }
    path[0] = 0;
    r = 0;
    while(1) {
        md = -1;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (path[i]<0) continue;
            if (md<0 || md>path[i]) {
                md = path[i];
                mi = i;
            }
        }
        if (md<0) break;
        r += md;
        flag[mi] = 1;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (path[i]<0 || path[i]>dis[mi][i]) path[i] = dis[mi][i];
        }
    }
    printf("%.2f\n", r);
    return 0;
}
