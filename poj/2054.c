#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { int b, n; } CNode;
CNode gpool[2048];
int gpc;
int nei[1024], tail[1024];
int cc[1024];
int nml[1024], nms[1024];
int gml, gms;
int heap[1024*2], hpc;
int heapi[1024];
void heapify(int s) {
    int ns, ms=s; 
    ns = s*2+1; if (ns>=hpc) return;
    int a, b;
    a = heap[ns]; b= heap[ms];
    long long la, lb;
    la = nms[a]; la*=nml[b];
    lb = nms[b]; lb*=nml[a];
    if (la>lb) ms=ns;
    ns = s*2+2;
    if (ns<hpc) {
        a = heap[ns]; b= heap[ms];
        la = nms[a]; la*=nml[b];
        lb = nms[b]; lb*=nml[a];
        if (la>lb) ms=ns;
    }
    if (ms==s) return;
    ns=heap[s]; heap[s]=heap[ms]; heap[ms]=ns;
    heapi[heap[s]]=s; heapi[heap[ms]]=ms;
    heapify(ms);
}
void adjust(int s) {
    int p, t;
    int a, b;
    long long la, lb;
    while(s) {
        p = (s-1)/2;
        a = heap[p]; b= heap[s];
        la = nms[a]; la*=nml[b];
        lb = nms[b]; lb*=nml[a];
        if (la>=lb) break;
        t=heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[s]]=s; heapi[heap[p]]=p;
        s=p;
    }
}
int ps[1024];
char flag[1024];
int main() {
    int n, r, i, t, c, j, pa, ntail;
    int a, b;
    while(1) {
        scanf("%d %d", &n, &r); if (n==0&&r==0) break;
        r--; gpc=0;
        for (i=0; i<n; i++) {
            scanf("%d", &cc[i]);
            nei[i]=-1; nml[i]=1; nms[i]=cc[i];
            flag[i]=0; tail[i]=-1;
            ps[i]=-1;
        }
        for (i=0; i<n-1; i++) {
            scanf("%d %d", &a, &b); a--; b--;
            ps[b]=a;
        }
        t=1; c=cc[r]; hpc=0; flag[r]=1;
        for (i=0; i<n; i++) {
            if (i==r) continue;
            heap[hpc] = i;
            heapi[i]=hpc++;
            adjust(hpc-1);
        }
        while(hpc) {
           a = heap[0]; 
           heap[0]=heap[--hpc]; heapi[heap[0]]=0; heapify(0);
           pa = ps[a];
           while (flag[pa]==2) pa = ps[pa];
           if (flag[pa]==1) {
               t++; c+=t*cc[a]; flag[a]=1;
               j = nei[a]; while(j!=-1) {
                   b = gpool[j].b;
                   t++;  c+= t*cc[b]; flag[b]=1;
                   j = gpool[j].n;
               }
           } else {
               ntail = tail[a];
               gpool[gpc].b = a; gpool[gpc].n=nei[a];
               if (ntail==-1) ntail = gpc;
               gpc++;
               if (tail[pa]==-1) {
                   nei[pa]=gpc-1; tail[pa]=ntail;
               } else {
                   gpool[tail[pa]].n=gpc-1;
                   tail[pa]=ntail;
               }
               nml[pa] += nml[a];
               nms[pa] += nms[a];
               adjust(heapi[pa]);
               flag[a]=2;
           }
        }
        printf("%d\n", c);
    }
    return 0;
}


