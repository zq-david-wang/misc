#include<stdio.h>
#include<stdlib.h>

int vs[20001];
int ps[20000], ds[20000];
int mycmp(const void *a, const void *b) {
    int ia = *((const int *)a);
    int ib = *((const int *)b);
    int i=0; while(1) {
        if (vs[ia+i] != vs[ib+i]) return vs[ia+i]-vs[ib+i];
        i++;
    }
    return 0;
}
typedef struct {int i, v;}HNode;
HNode heap[20000];
int hpc;
int hi[20000];
void heapify(int s) {
    int ns, ms=s;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ms].v > heap[ns].v) ms = ns;
    ns = s*2+2;
    if (ns<hpc && heap[ms].v > heap[ns].v) ms=ns;
    if (ms==s) return;
    HNode t = heap[ms]; heap[ms] = heap[s]; heap[s] = t;
    hi[heap[ms].i] = ms;
    hi[heap[s].i] = s;
    heapify(ms);
}
void adjust(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].v <= heap[s].v) break;
        t = heap[p]; heap[p] = heap[s]; heap[s] = t;
        hi[heap[p].i] = p;
        hi[heap[s].i] = s;
        s = p;
    }
}

int main() {
    int n, k, i;
    scanf("%d %d", &n, &k);
    for (i=0; i<n; i++) scanf("%d", &vs[i]);
    vs[n] = -1;
    for (i=0; i<n; i++) ps[i] = i;
    qsort(ps, n, sizeof(ps[0]), mycmp);
    int i1, i2, d;
    for (i=1; i<n; i++) {
        i1 = ps[i-1]; i2 = ps[i];
        d = 0; while(1) {
            if (vs[i1+d]!=vs[i2+d]) break;
            d++;
        }
        ds[i-1] = d;
    }
    int m = 0;
    for (i=0; i<k-1; i++) { heap[i].i = i; heap[i].v = ds[i]; hi[i]=i;}
    hpc = k-1; 
    for (i=hpc-1; i>=0; i--) heapify(i);
    if (m<heap[0].v) m = heap[0].v;
    for (i=k-1; i<n-1; i++) {
        // for (j=0; j<hpc; j++) if (hi[heap[j].i] != j) printf("error\n");
        // replace ds[i-k+1] with ds[i]
        i1 = hi[i-k+1];
        heap[i1].i = i;
        hi[i] = i1;
        if (heap[i1].v > ds[i]) {
            heap[i1].v = ds[i];
            adjust(i1);
        } else {
            heap[i1].v = ds[i];
            heapify(i1);
        }
        if (m<heap[0].v) m = heap[0].v;
    }
    printf("%d\n", m);
    return 0;
}
