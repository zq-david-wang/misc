#include<stdio.h>
int edgea[21000], edgeb[21000], edged[21000];
#define INF 0x7fffffffffffffL
long long dis[1001];
char map[1001][1001];
int main() {
    int n, ml, md, i, j;
    int a, b, d, ec=0;
    long long dir;
    char relax;
    scanf("%d %d %d", &n, &ml, &md);
    for (i=1; i<=n; i++) for (j=1; j<=n; j++) map[i][j] = 0;
    for (i=0; i<ml; i++) {
        scanf("%d %d %d", &a, &b, &d);
        edgea[ec] = a; edgeb[ec] = b; edged[ec] = d;
        ec++;
        if (a+1==b) {
            edgea[ec] = b; edgeb[ec] = a; edged[ec] = 0;
            map[a][b] = 1;
            ec++;
        }
    }
    for (i=0; i<md; i++) {
        scanf("%d %d %d", &a, &b, &d);
        edgea[ec] = b; edgeb[ec] = a; edged[ec] = -d;
        ec++;
        if (a+1==b) map[a][b] = 1;
    }
    for (i=1; i<n; i++) if (map[i][i+1]==0) {
        edgea[ec] = i+1; edgeb[ec] = i; edged[ec] = 0;
        ec++;
    }
    // bellman ford
    for (i=2; i<=n; i++) dis[i] = INF;
    dis[1] = 0;
    for (i=0; i<=n; i++) {
        relax = 0;
        for (j=0; j<ec; j++) {
            a = edgea[j]; b = edgeb[j]; d = edged[j];
            if (dis[a]+d<dis[b]) {
                dis[b] = dis[a]+d;
                relax = 1;
                // printf("relax %d to %lld, using %d->%d:%d\n", b, dis[b], a, b, d);
            }
        }
        if (relax==0) break;
    }
    if (dis[n]==INF) printf("-2\n");
    else {
        dir = dis[1]-dis[n];
        // for (i=1; i<=n; i++) printf("%d:%lld,", i, dis[i]);printf("\n");
        for (i=1; i<n; i++) {
            if (dir>=0 && (dis[i]-dis[i+1]) < 0) break;
            if (dir<=0 && (dis[i]-dis[i+1]) > 0) break;
        }
        if (i==n) {
            if (relax) printf("-2\n");
            else {
                if (dir<0)dir = -dir;
                printf("%lld\n", dir);
            }
        } else printf("-1\n");
    }
    return 0;
}
