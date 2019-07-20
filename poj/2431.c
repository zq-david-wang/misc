#include<stdio.h>
#include<stdlib.h>

typedef struct { int d, f; }SNode;
SNode stop[10000];
int mycmp(const void *a, const void *b) {
    return ((const SNode*)b)->d - ((const SNode*)a)->d;
}

int heap[10000];
int hpc;
void heapify(int s) {
    int ns, ms=s;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ms]<heap[ns]) ms=ns;
    ns = s*2+2;
    if (ns<hpc && heap[ms]<heap[ns]) ms=ns;
    if (s==ms) return;
    int t=heap[s]; heap[s]=heap[ms]; heap[ms]=t;
    heapify(ms);
}
void adjust() {
    int s = hpc-1;
    int p, t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p]>=heap[s]) break;
        t = heap[p]; heap[p]=heap[s]; heap[s]=t;
        s = p;
    }
}
int main() {
    int n, i, l, p;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &stop[i].d, &stop[i].f);
    }
    scanf("%d %d", &l, &p);
    qsort(stop, n, sizeof(stop[0]), mycmp);
    hpc = 0;
    for (i=0; i<n; i++) if (stop[i].d<=l) break;
    int rc = 0;
    for (; i<n; i++) {
        if (p >= l) break;
        while ((l-p)>stop[i].d) {
            if (hpc==0) break;
            p += heap[0];
            rc++;
            hpc--;
            heap[0] = heap[hpc];
            heapify(0);
        }
        if ((l-p)>stop[i].d) break;
        heap[hpc++] = stop[i].f;
        adjust();
    }
    while(p<l) {
        if (hpc==0) break;
        p += heap[0];
        rc++;
        hpc--;
        heap[0] = heap[hpc];
        heapify(0);
    }
    if (p<l) printf("-1\n");
    else printf("%d\n", rc);
    return 0;
}
