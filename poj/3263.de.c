#include<stdio.h>

unsigned int edges[8000000];
#define INF 0x7fffffff
int dis[10001];
int main() {
    int n, i, h, r, j, k;
    int ec = 0, a, b, d;
    scanf("%d %d %d %d", &n, &i, &h, &r);
    for (j=0; j<r; j++) {
        scanf("%d %d", &a, &b);
        edges[ec++] = (b<<16) | a;
        if (a<b) for (k=a+1; k<b; k++) edges[ec++] = 0x80000000|(a<<16)|k;
        else for (k=b+1; k<a; k++) edges[ec++] = 0x80000000|(a<<16)|k;
    } 
    for (j=1; j<=n; j++) {
        edges[ec++] = j;
        dis[j] = INF;
    }
    if (ec>=sizeof(edges)/sizeof(edges[0])) printf("need more edges\n");
    dis[0] = 0;
    char relax;
    for (j=0; j<=n; j++) {
        relax = 0;
        for (k=0; k<ec; k++) {
            if (edges[k]&0x80000000) d = -1;
            else d = 0;
            a = (edges[k]>>16)&0x7fff;
            b = edges[k]&0xffff;
            if (dis[a] == INF) continue;
            if (dis[a]+d<dis[b]) {
                dis[b] = dis[a]+d;
                relax = 1;
            }
        }
        if (relax==0) break;
    }
    if (relax == 1) printf("error\n");
    d = h-dis[i];
    for (j=1; j<=n; j++) printf("%d\n", d+dis[j]);
    return 0;
}
