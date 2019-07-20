#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct { int b, e; } jump[64];
int ps[1024];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
struct { int b, n, d; } npool[10240];
int npc;

int nei[1024];
int dis[1024];
#define MOD 1024
int queue[MOD];
char inque[MOD];
char mark[1024];
#define INF 0x7fffffff
int findi(int v, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m=(l+h)/2;
        if (ps[m]==v) return m;
        if (ps[m]>v) h=m-1;
        else l=m+1;
    }
    return -1;
}
int main() {
    int w, s, p, i, b, e, j, k;
    int ia, ib, head, tail;
    int m, nm, d;
    char mm[8];
    while(1) {
        scanf("%d", &w); if (w==0) break;
        scanf("%d %d", &s, &p);
        j=0; ps[j++]=0; ps[j++]=w;
        for (i=0; i<p; i++) {
            scanf("%d %d", &b, &e);
            jump[i].b=b; jump[i].e=e;
            for (k=0; k<s; k++) { ps[j++] = b+k; ps[j++] = e+k; }
            for (k=1; k<s; k++) { if (b-k<=0) break; ps[j++] = b-k; ps[j++] = e-k; }
        }
        qsort(ps, j, sizeof(ps[0]), mycmp);
        k=1; for (i=1; i<j; i++) {
            if (ps[i]==ps[i-1]) continue;
            ps[k++] = ps[i];
        }
        for (i=0; i<k; i++) mark[i]=0;
        for (i=0; i<p; i++) {
            ia = findi(jump[i].b, k);
            mark[ia]=1;
        }
        // for (i=0; i<k; i++) printf("%d(%d) ", ps[i], i); printf("\n");
        npc=0; for (i=0; i<k; i++) nei[i]=-1;
        for (i=0; i<k-1; i++) {
            if (mark[i]) {
                continue;
            }
            m = ps[i];
            ib=i+1;
            for (j=0; j<s; j++) mm[j]=0;
            while(ib<k) {
                nm = ps[ib];
                for (j=0; j<s; j++) if (mm[j]==0) break;
                if (j==s) break;
                if (mm[(nm-m)%s]==0) {
                    mm[(nm-m)%s]=1;
                    d = (nm-m+s-1)/s;
                    npool[npc].b=ib; npool[npc].n=nei[i]; npool[npc].d=d; nei[i]=npc++;
                }
                ib++;
            }
        }
        for (i=0; i<p; i++) {
            ia=findi(jump[i].b, k);
            ib=findi(jump[i].e, k);
            npool[npc].b=ib; npool[npc].n=nei[ia]; npool[npc].d=0; nei[ia]=npc++;
        }
        /* 
        for (i=0; i<k; i++) {
            printf("nei %d(%d):", i, ps[i]);
            j = nei[i]; while(j!=-1) {
                ib = npool[j].b;
                d=npool[j].d;
                j=npool[j].n;
                printf(" %d(%d):%d", ib, ps[ib], d);
            }
            printf("\n");
        }
        */
        // find shortest path between 0 and w
        for (i=0; i<k; i++) { dis[i]=INF; inque[i]=0; }
        dis[0]=0; inque[0]=1; head=tail=0; queue[head++]=0;
        while(head != tail) {
            i=queue[tail++]; tail %= MOD;
            j = nei[i]; inque[i]=0;
            while(j!=-1) {
                ib = npool[j].b;
                d = npool[j].d;
                if (d != INF && d+dis[i]<dis[ib]) {
                    dis[ib]=d+dis[i];
                    if (inque[ib]==0) {
                        inque[ib]=1;
                        queue[head++] = ib; head %=MOD;
                    }
                }
                j = npool[j].n;
            }
        }
        // for (i=0; i<k; i++) printf("%d(%d):%d\n", i, ps[i], dis[i]);
        ib = findi(w, k);
        printf("%d\n", dis[ib]);
    }
    return 0;
}


