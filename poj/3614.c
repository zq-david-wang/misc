#include<stdio.h>
#include<stdlib.h>

typedef struct { int s, e; } RNode;
RNode rqs[2500];
int mycmp(const void *a, const void *b) {
    const RNode *pa = (const RNode*)a;
    const RNode *pb = (const RNode*)b;
    return pa->e - pb->e;
}
int cs[1001];
typedef struct _T {
    struct _T *n;
    int s, e;
}ENode;
ENode cows[2501];

int main() {
    int c, l, i;
    int a, b;
    ENode root, *p;
    scanf("%d %d", &c, &l);
    for (i=0; i<c; i++) {
        scanf("%d %d", &rqs[i].s, &rqs[i].e);
    }
    qsort(rqs, c, sizeof(rqs[0]), mycmp);
    for (i=0; i<c; i++) {
        cows[i].s = rqs[i].s;
        cows[i].e = rqs[i].e;
        cows[i].n = &cows[i+1];
    }
    cows[c-1].n = NULL;
    root.n = &cows[0];
    for (i=0; i<=1000; i++)cs[i] = 0;
    for (i=0; i<l; i++) {
        scanf("%d %d", &a, &b);
        cs[a] += b;
    }
    int rc = 0;
    for (i=1; i<=1000; i++) {
        p = &root;
        while(cs[i]) {
            if (p->n==NULL) break;
            if (p->n->e<i) {
                p->n = p->n->n;
            } else {
                if (p->n->s <= i) {
                    p->n = p->n->n;
                    cs[i]--;
                    rc++;
                } else p = p->n;
            }
        }
    }
    printf("%d\n", rc);
    return 0;
}
