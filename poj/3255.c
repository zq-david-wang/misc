#include<stdio.h>

typedef struct _T{
    struct _T *n;
    int b, d;
}Edge;
Edge gpool[200000];
Edge *nodes[5001];
int queue[10000];
int path1[5001], path2[5001];
char flag[5001];
#define INF 0x7fffffff
int main() {
    int n, r, i;
    int a, b, d, gpc=0;
    Edge *p;
    scanf("%d %d", &n, &r);
    for (i=1; i<=n; i++) {
        nodes[i] = NULL;
        path1[i] = INF;
        path2[i] = INF;
        flag[i] = 0;
    }
    for (i=0; i<r; i++) {
        scanf("%d %d %d", &a, &b, &d);
        p = &gpool[gpc++]; p->b = b; p->d = d; p->n = nodes[a]; nodes[a] = p;
        p = &gpool[gpc++]; p->b = a; p->d = d; p->n = nodes[b]; nodes[b] = p;
    }
    int qhead=0, qtail=0;
    path1[1] = 0;
    queue[qhead++] = 1;
    flag[1] = 1;
    while(qtail!=qhead) {
        a = queue[qtail++];
        flag[a] = 0;
        qtail %= 8000;
        p = nodes[a];
        while(p!=NULL) {
            b = p->b;
            d = p->d;
            if (path1[a]+d < path1[b]) {
                path2[b] = path1[b];
                path1[b] = path1[a]+d;
                if (flag[b]==0) {
                    queue[qhead++] = b;
                    qhead %= 8000;
                    flag[b] = 1;
                }
            } else if (path1[a]+d > path1[b]) {
                if (path1[a]+d < path2[b]) {
                    path2[b] = path1[a]+d;
                    if (flag[b]==0) {
                        queue[qhead++] = b;
                        qhead %= 8000;
                        flag[b] = 1;
                    }
                }
            }
            if (path2[a] != INF && path2[a]+d < path2[b]) {
                path2[b] = path2[a]+d;
                if (flag[b]==0) {
                    queue[qhead++] = b;
                    qhead %= 8000;
                    flag[b] = 1;
                }
            }
            p = p->n;
        }
    }
    printf("%d\n", path2[n]);
    return 0;
}
