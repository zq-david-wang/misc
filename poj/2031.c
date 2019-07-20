#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double xs[128], ys[128], zs[128], rs[128];
double map[128][128];
double dis[128];
char flag[128];
int main() {
    int n, i, j, di;
    double d, c;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) scanf("%lf %lf %lf %lf", &xs[i], &ys[i], &zs[i], &rs[i]);
        for (i=0; i<n; i++) {
            map[i][i]=0;
            for (j=i+1; j<n; j++) {
                d =  sqrt((xs[i]-xs[j])*(xs[i]-xs[j])+(ys[i]-ys[j])*(ys[i]-ys[j])+(zs[i]-zs[j])*(zs[i]-zs[j]));
                d -= (rs[i]+rs[j]);
                if (d<0) d=0;
                map[i][j]=map[j][i]=d;
            }
            dis[i]=-1;
            flag[i]=0;
        }
        dis[0]=0; c=0;
        while(1) {
            d = -1;
            for (i=0; i<n; i++) {
                if (flag[i]) continue;
                if (dis[i]<0) continue;
                if (d<0||d>dis[i]) {
                    d= dis[i]; di=i;
                }
            }
            if (d<0) break;
            c+=d;
            flag[di]=1;
            for (i=0; i<n; i++) {
                if (flag[i]) continue;
                if (dis[i]<0||map[di][i]<dis[i]) dis[i]=map[di][i];
            }
        }
        printf("%.3f\n", c);
    }
    return 0;
}


