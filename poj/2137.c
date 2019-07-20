#include<stdio.h>
#include<string.h>
#include<math.h>

int pc[101];
typedef struct { int x, y; }Point;
Point ps[100][40];
char flag[101][40];
double dp[101][40];
int gn;
Point end;
double dfs(int i, int s) {
    if (flag[i][s]) return dp[i][s];
    double r=-1;
    int dx, dy;
    if (i==gn-1) {
        dx = end.x-ps[i][s].x;
        dy = end.y-ps[i][s].y;
        r = sqrt(dx*dx+dy*dy);
    } else {
        double d;
        int j; for (j=0; j<pc[i+1]; j++) {
            dx = ps[i][s].x-ps[i+1][j].x;
            dy = ps[i][s].y-ps[i+1][j].y;
            d = sqrt(dx*dx+dy*dy);
            d += dfs(i+1, j);
            if (r<0 || r>d) r = d;
        } 
    }
    flag[i][s] = 1;
    dp[i][s] = r;
    return r;
}
int main() {
    int n, i;
    int j, x, y;
    scanf("%d", &n);
    gn = n;
    for (i=0; i<n; i++) {
        scanf("%d", &pc[i]);
        for (j=0; j<pc[i]; j++) {
            scanf("%d %d", &x, &y);
            ps[i][j].x = x;
            ps[i][j].y = y;
        }
    }
    double mr = -1, r;
    for (i=0; i<pc[0]; i++) {
        end = ps[0][i];
        // reset cache
        memset(flag, 0, sizeof(flag));
        r = dfs(0, i);
        if (mr<0 || mr>r) mr = r;
    }
    mr *= 100;
    i = mr;
    printf("%d\n", i);
    return 0;
}
