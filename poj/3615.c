#include<stdio.h>

int mpath[301][301];
char flag[301];
int map[301][301];
#define INF 0x3fffffff

typedef struct _T{
    struct _T *n;
    int b, h;
}ENode;
ENode gpool[25000];
int gpc;
ENode *nei[301];

int main() {
    int n, m, t, i, j;
    int mp, mi, a, b, h;
    scanf("%d %d %d", &n, &m, &t);
    for (i=1; i<=n; i++) for (j=1; j<=n; j++) map[i][j] = INF;
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &h);
        if (map[a][b]>h)map[a][b] = h;
    }
    gpc = 0;
    ENode *p;
    for (i=1; i<=n; i++) {
        nei[i] = NULL;
        for (j=1; j<=n; j++) {
            if (map[i][j]==INF) continue;
            p = &gpool[gpc++]; p->b = j; p->h = map[i][j]; p->n=nei[i]; nei[i] = p;
        }
    }
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) {
            mpath[i][j] = INF;
            flag[j] = 0;
        }
        mpath[i][i] = 0;
        while(1) {
            mp = INF;
            for (j=1; j<=n; j++) {
                if (flag[j]) continue;
                if (mp>mpath[i][j]) {
                    mp = mpath[i][j];
                    mi = j;
                }
            }
            if (mp==INF) break;
            flag[mi] = 1;
            p = nei[mi];
            while(p!=NULL) {
                j = p->b;
                if (flag[j]==0) {
                    mp = mpath[i][mi];
                    if (mp<p->h) mp = p->h;
                    if (mp<mpath[i][j]) {
                        mpath[i][j] = mp;
                    }
                }
                p = p->n;
            }
        }
    }
    for (i=0; i<t; i++) {
        scanf("%d %d", &a, &b);
        if (mpath[a][b]==INF) printf("-1\n");
        else printf("%d\n", mpath[a][b]);
    }
    return 0;
}
