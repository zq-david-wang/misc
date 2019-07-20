#include<stdio.h>

struct { int b, n; } pool[100000+4];
int pc;
int nei[100000+4];
int dc[100000+4];
typedef struct {
    int c, i;
}HNode;
HNode heap1[100000], heap2[100000];
int heapi[100000+4];
int hpc1, hpc2;
void adjust(HNode *heap, int i, int hpc) {
    int p;
    HNode t;
    while(i>0) {
        p = (i-1)/2;
        if (heap[p].c<=heap[i].c) break;
        t=heap[p]; heap[p]=heap[i];heap[i]=t;
        heapi[heap[p].i]=p;
        heapi[heap[i].i]=i;
        i=p;
    }
}

void heapify(HNode *heap, int s, int hpc) {
    int ms=s, ns; 
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ns].c<heap[ms].c) ms=ns;
    ns = s*2+2;
    if (ns<hpc && heap[ns].c<heap[ms].c) ms=ns;
    if (ms==s) return;
    HNode t;
    t=heap[ms];heap[ms]=heap[s];heap[s]=t;
    heapi[heap[ms].i]=ms;
    heapi[heap[s].i]=s;
}

int count(int dvd, int n1, int n2) {
    int c=0, i, j, b;
    // printf("count from dvd %d\n", dvd);
    while(1) {
        if (hpc1==0&&hpc2==0)break;
        if (dvd==0) {
            while(hpc1>0) {
                if (heap1[0].c) break;
                i = heap1[0].i;
                // printf("install package %d via dvd %d, with d %d\n", i, dvd, heap1[0].c);
                hpc1--; heap1[0]=heap1[hpc1]; heapi[heap1[0].i]=0; heapify(heap1, 0, hpc1);
                j = nei[i]; while(j>=0) {
                    b = pool[j].b;
                    if (b<=n1) {
                        heap1[heapi[b]].c--;
                        adjust(heap1, heapi[b], hpc1);
                    } else {
                        heap2[heapi[b]].c--;
                        adjust(heap2, heapi[b], hpc2);
                    }
                    j = pool[j].n;
                }
            }
        } else {
            while(hpc2>0) {
                if (heap2[0].c) break;
                i = heap2[0].i;
                // printf("install package %d via dvd %d, with d %d\n", i, dvd, heap2[0].c);
                hpc2--; heap2[0]=heap2[hpc2]; heapi[heap2[0].i]=0; heapify(heap2, 0, hpc2);
                j = nei[i]; while(j>=0) {
                    b = pool[j].b;
                    if (b<=n1) {
                        heap1[heapi[b]].c--;
                        adjust(heap1, heapi[b], hpc1);
                    } else {
                        heap2[heapi[b]].c--;
                        adjust(heap2, heapi[b], hpc2);
                    }
                    j = pool[j].n;
                }
            }

        }
        dvd = (dvd+1)&1; c++;
    }
    return c;
}
int main() {
    int n1, n2, d, i;
    int a, b;
    int c1, c2, dvd;
    while(1) {
        scanf("%d %d %d", &n1, &n2, &d);
        if (n1==0&&n2==0) break;
        pc=0;
        for (i=1; i<=n1+n2; i++) { nei[i]=-1; dc[i]=0; }
        for (i=0; i<d; i++) {
            scanf("%d %d", &a, &b);
            pool[pc].b=a; pool[pc].n=nei[b];nei[b]=pc++;
            dc[a]++;
        }
        // try 1 first,  build head
        hpc1=0; for (i=1; i<=n1; i++) {
            heap1[hpc1].c = dc[i];
            heap1[hpc1].i = i;
            heapi[i] = hpc1++;
            adjust(heap1, hpc1-1, hpc1);
        }
        hpc2=0; for (i=n1+1; i<=n1+n2; i++) {
            heap2[hpc2].c = dc[i];
            heap2[hpc2].i = i;
            heapi[i] = hpc2++;
            adjust(heap2, hpc2-1, hpc2);
        }
        c1 = count(0, n1, n2);
        hpc1=0; for (i=1; i<=n1; i++) {
            heap1[hpc1].c = dc[i];
            heap1[hpc1].i = i;
            heapi[i] = hpc1++;
            adjust(heap1, hpc1-1, hpc1);
        }
        hpc2=0; for (i=n1+1; i<=n1+n2; i++) {
            heap2[hpc2].c = dc[i];
            heap2[hpc2].i = i;
            heapi[i] = hpc2++;
            adjust(heap2, hpc2-1, hpc2);
        }
        c2 = count(1, n1, n2);
        if (c1>c2) c1=c2;
        printf("%d\n", c1+1);
    }
    return 0;
}
