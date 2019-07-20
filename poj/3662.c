#include<stdio.h>
#include<stdlib.h>

typedef struct _T {
    struct _T *n;
    int b, l;
}ENode;
ENode pool[20000];
ENode *nei[1001];
short cap[1001];
int dis[10000];
int vs[1001];
int pt[1001];
#define INF 0x7fffffff
int queue[2000];
char inq[1001];
#define QMOD 2000
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int main() {
    int n, p, k, i, j;
    int a, b, l, pc=0, dc=0, cd;
    ENode *ep;
    scanf("%d %d %d\n", &n, &p, &k);
    for (i=1; i<=n; i++) { 
        nei[i] = NULL;
    }
    for (i=0; i<p; i++) {
        scanf("%d %d %d", &a, &b, &l);
        ep=&pool[pc++]; ep->b=b; ep->l=l; ep->n=nei[a]; nei[a]=ep;
        ep=&pool[pc++]; ep->b=a; ep->l=l; ep->n=nei[b]; nei[b]=ep;
        dis[i] = l;
    }
    dis[p] = 0;
    qsort(dis, p+1, sizeof(dis[0]), mycmp); 
    for (i=0; i<=p; i++) {
        if (i>0&&dis[i]==dis[i-1]) continue;
        dis[dc++] = dis[i];
    }
    int li=0, hi=dc-1, mi;
    int head, tail;
    while(li<=hi) {
        mi = (li+hi)/2;
        cd = dis[mi];
        // printf("try min cost %d\n", cd);
        for (i=1; i<=n; i++) { cap[i] = -1; inq[i] = 0; }
        head = tail = 0;
        queue[head++] = 1;
        cap[1] = k;
        inq[1] = 1;
        while(tail!=head) {
            a = queue[tail++]; tail %= QMOD;
            if (a==n) break;
            // printf("process queue %d, cap: %d\n", a, cap[a]);
            ep = nei[a];
            inq[a] = 0;
            while(ep != NULL) {
                b = ep->b;
                if (cap[b] < cap[a]) {
                    if (ep->l <= cd) {
                        cap[b]=cap[a];
                        if (inq[b]==0) {
                            queue[head++] = b; head %= QMOD;
                            inq[b] = 1;
                        }
                    } else {
                        if (cap[a]>0 && cap[a]-1>cap[b]) {
                            cap[b] = cap[a]-1;
                            if (inq[b]==0) {
                                queue[head++] = b; head %= QMOD;
                                inq[b] = 1;
                            }
                        }
                    }
                }
                ep = ep->n;
            }
        }
        if (a==n) {
            if (hi==mi) break;
            hi = mi;
        } else {
            li = mi+1;
        }
    }
    if (li>hi) printf("-1\n");
    else printf("%d\n", dis[hi]);

    return 0;
}
