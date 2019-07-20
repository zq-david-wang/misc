#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { int b, n; } CNode;
CNode gpool[2048];
int gpc;
int nei[1024];
int cc[1024], cs[1024], ccc[1024];
int count(int r) {
    int j = nei[r], b;
    int c = cc[r], ic=1;
    while(j!=-1) {
        b = gpool[j].b;
        c += count(b);
        j = gpool[j].n;
        ic += ccc[b];
    }
    cs[r]=c;
    ccc[r]=ic;
    return c;
}
int heap[1024], hpc;
void heapify(int s) {
    int ns, ms=s; 
    ns = s*2+1; if (ns>=hpc) return;
    int a, b;
    a = heap[ns]; b= heap[ms];
    long long la, lb;
    la = cs[a]; la*=ccc[b];
    lb = cs[b]; lb*=ccc[a];
    if (la>lb||(la==lb&&cc[a]>cc[b])) ms=ns;
    ns = s*2+2;
    if (ns<hpc) {
        a = heap[ns]; b= heap[ms];
        la = cs[a]; la*=ccc[b];
        lb = cs[b]; lb*=ccc[a];
        if (la>lb||(la==lb&&cc[a]>cc[b])) ms=ns;
    }
    if (ms==s) return;
    ns=heap[s]; heap[s]=heap[ms]; heap[ms]=ns;
    heapify(ms);
}
void adjust(int s) {
    int p, t;
    int a, b;
    long long la, lb;
    while(s) {
        p = (s-1)/2;
        a = heap[p]; b= heap[s];
        la = cs[a]; la*=ccc[b];
        lb = cs[b]; lb*=ccc[a];
        if (la>lb||(la==lb&&cc[a]>=cc[b])) break;
        t=heap[p]; heap[p]=heap[s]; heap[s]=t;
        s=p;
    }
}
int main() {
    int n, r, i, t, c, j;
    int a, b;
    while(1) {
        scanf("%d %d", &n, &r); if (n==0&&r==0) break;
        r--; gpc=0;
        for (i=0; i<n; i++) nei[i]=-1;
        for (i=0; i<n; i++) scanf("%d", &cc[i]);
        for (i=0; i<n-1; i++) {
            scanf("%d %d", &a, &b); a--; b--;
            gpool[gpc].b=b; gpool[gpc].n=nei[a]; nei[a]=gpc++;
        }
        count(r);
        hpc=0; heap[hpc++] = r;
        t=0; c=0;
        while(hpc) {
           t++; 
           a = heap[0]; c += cc[a]*t;
           heap[0]=heap[--hpc];
           heapify(0);
           j = nei[a]; while(j!=-1) {
               b = gpool[j].b;
               j = gpool[j].n;
               heap[hpc++] = b; adjust(hpc-1);
           }
        }
        printf("%d\n", c);
    }
    return 0;
}


