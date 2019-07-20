#include<stdio.h>

int board[256*256];
unsigned char cache[256][256];
typedef struct {
    short v, i;
}HNode;
HNode heap[256];
int hpc, heapi[256];
unsigned char maxcache[256*256];
unsigned char mincache[256*256];
unsigned char tcache[256];
void heapify(int s) {
    int ms=s, ns;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ms].v<heap[ns].v) ms = ns;
    ns = s*2+2;
    if (ns<hpc && heap[ms].v<heap[ns].v) ms = ns;
    if (ms==s) return;
    HNode t;
    t=heap[ms]; heap[ms]=heap[s]; heap[s]=t;
    heapi[heap[s].i]=s;
    heapi[heap[ms].i]=ms;
    heapify(ms);
}
void adjust(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].v>=heap[s].v) break;
        t = heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[s].i]=s;
        heapi[heap[p].i]=p;
        s = p;
    }
}
void heapify2(int s) {
    int ms=s, ns;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ms].v>heap[ns].v) ms = ns;
    ns = s*2+2;
    if (ns<hpc && heap[ms].v>heap[ns].v) ms = ns;
    if (ms==s) return;
    HNode t;
    t=heap[ms]; heap[ms]=heap[s]; heap[s]=t;
    heapi[heap[s].i]=s;
    heapi[heap[ms].i]=ms;
    heapify2(ms);
}
void adjust2(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].v<=heap[s].v) break;
        t = heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[s].i]=s;
        heapi[heap[p].i]=p;
        s = p;
    }
}
void pmax(int *v, int n, int b, unsigned char *o) {
    hpc = 0;
    int i, j; for (i=0; i<b-1; i++) {
        heapi[i] = hpc;
        heap[hpc].v = v[i];
        heap[hpc].i = i;
        hpc++;
        adjust(hpc-1);
    }
    for (i=0; i+b<=n; i++) {
        heap[hpc].v = v[i+b-1];
        heap[hpc].i = i+b-1;
        heapi[i+b-1] = hpc;
        hpc++; adjust(hpc-1);
        o[i] = heap[0].v;
        j = heapi[i];
        heap[j] = heap[--hpc];
        heapi[heap[j].i] = j;
        heapify(j);
    }
}
void pmin(int *v, int n, int b, unsigned char *o) {
    hpc = 0;
    int i, j; for (i=0; i<b-1; i++) {
        heapi[i] = hpc;
        heap[hpc].v = v[i];
        heap[hpc].i = i;
        hpc++;
        adjust2(hpc-1);
    }
    for (i=0; i+b<=n; i++) {
        heap[hpc].v = v[i+b-1];
        heap[hpc].i = i+b-1;
        heapi[i+b-1] = hpc;
        hpc++; adjust2(hpc-1);
        o[i] = heap[0].v;
        j = heapi[i];
        heap[j] = heap[--hpc];
        heapi[heap[j].i] = j;
        heapify2(j);
    }
}
int vs[256];
int main() {
    int n, b, k, i, j;
    int r, c;
    scanf("%d %d %d", &n, &b, &k);
    for (i=0; i<n; i++) for (j=0; j<n; j++) scanf("%d", &board[i*n+j]);
    for (i=0; i<n; i++) { 
        pmax(&board[i*n], n, b, &maxcache[i*n]);
        pmin(&board[i*n], n, b, &mincache[i*n]);
    }
    for (i=0; i+b<=n; i++) {
        for (j=0; j<n; j++) {
            vs[j] = maxcache[j*n+i];
        }
        pmax(vs, n, b, tcache);
        for (j=0; j+b<=n; j++) {
            cache[j][i] = tcache[j];
        }
        for (j=0; j<n; j++) {
            vs[j] = mincache[j*n+i];
        }
        pmin(vs, n, b, tcache);
        for (j=0; j+b<=n; j++) {
            cache[j][i] -= tcache[j];
        }
    }
    //
    for (i=0; i<k; i++) {
        scanf("%d %d", &r, &c);
        r--; c--;
        printf("%d\n", cache[r][c]);
    }
    return 0;
}
