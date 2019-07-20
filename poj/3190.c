#include<stdio.h>
#include<stdlib.h>

typedef struct {int s, e, i;}CNode;
CNode cw[50000];
int mycmp(const void *a, const void *b) {
    return ((const CNode*)a)->s - ((const CNode*)b)->s;
}
int pos[50000];

typedef struct {int t, i; } HNode;
HNode heap[50000];
int hpc;
void heapify(int s) {
    int ns, ms=s;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ns].t < heap[ms].t) ms = ns;
    ns = s*2+2;
    if (ns<hpc && heap[ns].t<heap[ms].t) ms = ns;
    if (ms==s) return;
    HNode t = heap[s]; heap[s] = heap[ms]; heap[ms] = t;
    heapify(ms);
}
void adjust(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].t<=heap[s].t) break;
        t = heap[p]; heap[p] = heap[s]; heap[s] = t;
        s = p;
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &cw[i].s, &cw[i].e);
        cw[i].i = i;
    }
    qsort(cw, n, sizeof(cw[0]), mycmp);
    // for (i=0; i<n; i++) printf("%d: %d,%d %d\n", i, cw[i].s, cw[i].e, cw[i].i);
    hpc = 0;
    for (i=0; i<n; i++) {
        if (hpc==0 || heap[0].t>=cw[i].s) {
            heap[hpc].t = cw[i].e;
            heap[hpc].i = hpc+1;
            pos[cw[i].i] = heap[hpc].i;
            hpc++;
            adjust(hpc-1);
        } else {
            pos[cw[i].i] = heap[0].i;
            heap[0].t = cw[i].e;
            heapify(0);
        }
    }
    printf("%d\n", hpc);
    for (i=0; i<n; i++) printf("%d\n", pos[i]);
    return 0;
}
