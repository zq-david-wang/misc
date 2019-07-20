#include<stdio.h>

int hs[101][101];
int speed[100][100];
#define INF 0xffffffffffffffffL
typedef struct {int r, c; unsigned long long t; }HNode;
HNode heap[10000];
int hpc;
int hi[100][100];
void heapify(int s) {
    int ns = s*2+1, ms=s;
    if (ns>=hpc) return;
    if (heap[ns].t < heap[ms].t) ms = ns;
    ns = s*2+2;
    if (ns<hpc && heap[ns].t<heap[ms].t) ms = ns;
    if (ms==s) return;
    HNode t = heap[s]; heap[s] = heap[ms]; heap[ms] = t;
    hi[heap[s].r][heap[s].c] = s;
    hi[heap[ms].r][heap[ms].c] = ms;
    heapify(ms);
}
void adjust(int e) {
    int p;
    HNode t;
    while(e>0) {
        p = (e-1)/2;
        if (heap[p].t <= heap[e].t) break;
        t = heap[p]; heap[p] = heap[e]; heap[e] = t;
        hi[heap[p].r][heap[p].c] = p;
        hi[heap[e].r][heap[e].c] = e;
        e = p;
    }
}
double tss[128];
int main() {
    int v, r, c, i, j, ni, ms;
    unsigned long long p, k;
    scanf("%d %d %d", &v, &r, &c);
    for (i=0; i<r; i++) for (j=0; j<c; j++) scanf("%d", &hs[i][j]);
    speed[0][0] = 0;
    ms = 0;
    for (i=1; i<c; i++) { 
        speed[0][i] = speed[0][i-1]+hs[0][i-1]-hs[0][i];
        if (ms<speed[0][i]) ms = speed[0][i];
    }
    for (i=1; i<r; i++) for (j=0; j<c; j++) {
        speed[i][j] = speed[i-1][j]+hs[i-1][j]-hs[i][j];
        if (ms<speed[i][j]) ms = speed[i][j];
    }
    // for (i=0; i<r; i++) { for (j=0; j<c; j++) printf("%d ", speed[i][j]); printf("\n");}
    hpc = 0;
    for (i=0; i<r; i++) for (j=0; j<c; j++) {
        heap[hpc].r = i;
        heap[hpc].c = j;
        heap[hpc].t = INF;
        hi[i][j] = hpc;
        hpc++;
    }
    heap[0].t = 0;
    while(hpc>0) {
        // for (i=0; i<hpc; i++) printf("%d:%d  %d,%d-->%llx\n", i, hi[heap[i].r][heap[i].c], heap[i].r, heap[i].c, heap[i].t); printf("---------\n");
        i = heap[0].r;
        j = heap[0].c;
        p = heap[0].t;
        if (i==r-1&&j==c-1) {
            break;
        }
        hpc--;
        hi[i][j] = -1;
        heap[0] = heap[hpc];
        hi[heap[0].r][heap[0].c] = 0;
        heapify(0);
        k = 1;
        k <<= (ms-speed[i][j]);
        k += p;
        // printf("%d,%d (%d) %llx %llx\n", i, j, speed[i][j], p, k);
        if (i>0) { ni = hi[i-1][j]; if (ni>=0 && k<heap[ni].t) {heap[ni].t = k; adjust(ni); }}
        if (i<r-1) { ni = hi[i+1][j]; if (ni>=0 && k<heap[ni].t) { heap[ni].t = k; adjust(ni);}}
        if (j>0) { ni = hi[i][j-1]; if (ni>=0 && k<heap[ni].t) {heap[ni].t = k; adjust(ni); }}
        if (j<c-1) { ni = hi[i][j+1]; if (ni>=0 && k<heap[ni].t) { heap[ni].t = k; adjust(ni);}}
    }
    tss[ms] = 1;
    for (i=ms-1; i>=0; i--) tss[i] = tss[i+1]/2;
    double rt = 0;
    // multiple the value by 2^-ms
    for (i=0; i<ms; i++) {
        if (p&1) rt += tss[i];
        p >>= 1;
    }
    rt += p;
    rt /= v;
    printf("%.2f\n", rt);
    return 0;
}
