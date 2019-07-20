#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct { int t, id, p; } HNode;
HNode heap[1024];
int hpc;
void heapify(int s) {
    int ns, ms=s;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ms].t>heap[ns].t||(heap[ms].t==heap[ns].t&&heap[ms].id>heap[ns].id)) ms=ns;
    ns = s*2+2;
    if (ns<hpc&&(heap[ms].t>heap[ns].t||(heap[ms].t==heap[ns].t&&heap[ms].id>heap[ns].id))) ms=ns;
    if (ms==s) return;
    HNode t = heap[ms]; heap[ms]=heap[s]; heap[s]=t;
    heapify(ms);
}
int main() {
    int id, p, n, i;
    hpc = 0;
    char b[16];
    while(1) {
        scanf("%s", b); if (b[0]=='#') break;
        scanf("%d %d", &id, &p);
        heap[hpc].t = p;
        heap[hpc].p = p;
        heap[hpc].id = id; hpc++;
    }
    for (i=(hpc+1)/2; i>=0; i--) heapify(i);
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        printf("%d\n", heap[0].id);
        heap[0].t += heap[0].p;
        heapify(0);
    }
    return 0;
}


