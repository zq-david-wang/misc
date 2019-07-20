#include<stdio.h>

typedef struct {int a, b, d;}PNode;
PNode ps[2500], ws[200];
long long  dis[501];
#define INF 0x7fffffffffffffffL
int main() {
    int f, n, m, w, i, j, k, o;
    int a, b;
    long long d;
    char stable;
    scanf("%d", &f);
    for (i=0; i<f; i++) {
        scanf("%d %d %d", &n, &m, &w);
        for (j=0; j<m; j++) scanf("%d %d %d", &ps[j].a, &ps[j].b, &ps[j].d);
        for (j=0; j<w; j++) scanf("%d %d %d", &ws[j].a, &ws[j].b, &ws[j].d);
        for (k=1; k<=n; k++) {
            for (j=1; j<=n; j++) dis[j] = INF;
            dis[k] = 0;
            for (o=0; o<n; o++) {
                stable = 1;
                for (j=0; j<m; j++) {
                    a = ps[j].a; b = ps[j].b; d = ps[j].d;
                    if (dis[a] != INF && dis[a] + d < dis[b]) { dis[b] = dis[a]+d; stable = 0; }
                    if (dis[b] != INF && dis[b] + d < dis[a]) { dis[a] = dis[b]+d; stable = 0; }
                }
                for (j=0; j<w; j++) {
                    a = ws[j].a; b= ws[j].b; d = -ws[j].d;
                    if (dis[a] != INF&&dis[a]+d<dis[b]) { dis[b] = dis[a]+d; stable=0; }
                }
                if (stable) break;
            }
            if (o==n) break;
        }
        if (o==n) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
