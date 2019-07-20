#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int x, y;
}Point;

Point cities[100000];
int mycmpx(const void *a, const void *b) {
    return ((const Point*)a)->x - ((const Point*)b)->x;
}
int mycmpy(const void *a, const void *b) {
    return ((const Point*)a)->y - ((const Point*)b)->y;
}
int dp[100001][10];
int gcd(int a, int b) {
    int t; while(a>0) {
        t=a; a=b%a; b=t;
    }
    return b;
}
int cs[100001];
int sum[100001];
int min1[100001];
int min2[100001];
int tvs[100001];
#define INF 0x7fffffff
typedef struct { int i, v; } HNode;
HNode heap[100001]; 
int hpc, heapi[100001];

void heapify(int s) {
    int ns, ms=s;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ns].v<heap[ms].v) ms=ns;
    ns = s*2+2;
    if (ns<hpc&&heap[ns].v<heap[ms].v) ms=ns;
    if (ms==s) return;
    HNode t=heap[ms]; heap[ms]=heap[s]; heap[s]=t;
    heapi[heap[ms].i]=ms;
    heapi[heap[s].i]=s;
    heapify(ms);
}

void adjust(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].v<=heap[s].v) break;
        t=heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[s].i]=s;
        heapi[heap[p].i]=p;
        s = p;
    }

}
int process(int nc, int n, int k) {
    // printf("process %d,%d %d\n", nc, n, k);
    int c=0, d, ss, mv, ej, i, j, tv, si, tc, r, nj, s;
    dp[nc][0]=n;
    for (i=nc-1; i>=0; i--) { c += cs[i]; d=c*k-n; if (d<0) d=-d; dp[i][0]=d; }
    sum[0]=0; for (i=1; i<=nc; i++) sum[i]=cs[i-1]+sum[i-1];
    for (i=1; i<k; i++) {
        dp[nc][i]=(i+1)*n;
        ss = sum[nc];
        c = 0; for (j=nc-1; j>=0; j--) { c+=cs[j]; if (c*k>=n) break; min1[j]=INF;}
        // printf("process %d, total sum is %d, start with %d\n", i, ss, c);
        mv = INF; ej = nc-1; for (;j>=0;j--) {
            while((c*k)>=n) {
                if (dp[ej+1][i-1]!=INF) {
                    tv = ss*k-n+dp[ej+1][i-1]; 
                    if (mv>tv) mv=tv;
                }
                ss-=cs[ej]; c-=cs[ej]; ej--;
            }
            // printf("min1 %d,%d ==> %d, c is %d, ej %d\n", i, j, mv, c, ej);
            min1[j]=mv; if (j) c += cs[j-1];
        }
        // printf("process %d min1 done\n", i);
        // min2 heap
        s=0; for (j=0; j<nc; j++) { s+=cs[j]; tvs[j] = n-s*k+dp[j+1][i-1]; }
        hpc=0; si=0; c=0;for (j=0; j<nc; j++) {
            while(si<nc) {
                tc = c+cs[si];
                if (tc*k>n) break;
                heap[hpc].i=si; heap[hpc].v=tvs[si]; heapi[si]=hpc; hpc++; adjust(hpc-1);
                c = tc; si++;
            }
            if (hpc>0) {
                min2[j]=heap[0].v;
                nj = heapi[j]; heap[nj] = heap[--hpc]; heapi[heap[nj].i]=nj; heapify(nj);
            } else min2[j]=INF;
            if (si<=j) { si++; c=0;}
            else { c-= cs[j]; }
        }
        for (j=nc-1; j>=0; j--) {
            r = n+dp[j][i-1];
            if (min1[j]!=INF) {
                d = min1[j]-sum[j]*k;
                if (r>d) r=d;
            }
            if (min2[j]!=INF) {
                d = min2[j]+sum[j]*k;
                if (r>d) r=d;
            }
            dp[j][i]=r;
            // printf("dp %d,%d==>%d\n", i, j, r);
        }
    }
    return dp[0][k-1];
}

int main() {
    int n, k, i, ci=0;
    int c1, c2, g, nc, c;
    while(1) {
        scanf("%d %d", &n, &k); if (n==0) break; ci++;
        for (i=0; i<n; i++) scanf("%d %d", &cities[i].x, &cities[i].y);
        //x
        qsort(cities, n, sizeof(cities[0]), mycmpx);
        nc=0; c=1; for (i=1; i<n; i++) {
            if (cities[i].x==cities[i-1].x) c++;
            else { cs[nc++]=c; c=1; }
        } cs[nc++]=c;
        c1 = process(nc, n, k);
        // y
        qsort(cities, n, sizeof(cities[0]), mycmpy);
        nc=0; c=1; for (i=1; i<n; i++) {
            if (cities[i].y==cities[i-1].y) c++;
            else { cs[nc++]=c; c=1; }
        } cs[nc++]=c;
        c2 = process(nc, n, k);
        // printf("c1 %d, c2 %d\n", c1, c2);
        if (c1>c2) c1=c2;
        c2 = k*k;
        g = gcd(c1, c2); c1/=g; c2/=g;
        printf("%d. %d/%d\n", ci, c1, c2);
    }
    return 0;
}
