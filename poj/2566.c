#include<stdio.h>
#include<stdlib.h>

int vs[100001];
#define INF 0x7fffffff
typedef struct {
    int t, si, ei, d, s;
}TNode;
TNode ts[100000];
int gk;
typedef struct { int i; long long v; }VNode;
VNode tempv[100001];
long long temps[100001];
int mycmp(const void *a, const void *b) {
    const VNode *pa = (const VNode *)a;
    const VNode *pb = (const VNode *)b;
    if (pa->v>pb->v) return 1;
    else if (pa->v<pb->v) return -1;
    else return 0;
}
void count(int s, int e) {
    int i;
    long long ss, d, dd;
    if (s==e) {
        ss = vs[s]; if (ss<0) ss=-ss;
        for (i=0; i<gk; i++) {
            d = ss-ts[i].t; if (d<0) d=-d;
            if (d<ts[i].d) { ts[i].d=d; ts[i].si=s; ts[i].ei=e; ts[i].s=ss;}
        }
        return;
    }
    int m = (s+e)/2;
    int l, h, mm;
    int j, k;
    count(s, m); count(m+1, e);
    ss=0; j=0; for (i=m; i>=s; i--) {tempv[j].i=i; tempv[j].v=ss+vs[i]; j++; ss+=vs[i];}
    qsort(tempv, j, sizeof(tempv[0]), mycmp);
    temps[m+1] = vs[m+1];
    for (i=m+2; i<=e; i++) temps[i] = temps[i-1]+vs[i];
    for (i=m+1; i<=e; i++) {
        for (k=0; k<gk; k++) {
            d = ts[k].t-temps[i];
            l=0; h=j-1; while(l<=h) {
                mm = (l+h)/2;
                if (tempv[mm].v==d) break;
                if (tempv[mm].v>d) { if (h==mm) break; h=mm; }
                else l=mm+1;
            }
            if (tempv[mm].v==d) {
                ts[k].d = 0; ts[k].si=tempv[mm].i; ts[k].ei=i; ts[k].s=ts[k].t;
            } else {
                ss = temps[i]+tempv[h].v; if (ss<0)ss=-ss;
                dd = ts[k].t-ss; if (dd<0) dd=-dd;
                if (dd<ts[k].d) { ts[k].d=dd; ts[k].si=tempv[h].i; ts[k].ei=i; ts[k].s=ss; }
                if (h>0) {
                    h--;
                    ss = temps[i]+tempv[h].v; if (ss<0)ss=-ss;
                    dd = ts[k].t-ss; if (dd<0) dd=-dd;
                    if (dd<ts[k].d) { ts[k].d=dd; ts[k].si=tempv[h].i; ts[k].ei=i; ts[k].s=ss;}
                }
            }
            // nagative
            d = 0-ts[k].t-temps[i];
            l=0; h=j-1; while(l<=h) {
                mm = (l+h)/2;
                if (tempv[mm].v==d) break;
                if (tempv[mm].v > d) { if (h==mm) break; h=mm; }
                else l=mm+1;
            }
            if (tempv[mm].v==d) {
                ts[k].d = 0; ts[k].si=tempv[mm].i; ts[k].ei=i; ts[k].s=ts[k].t;
            } else {
                ss = temps[i]+tempv[h].v; if (ss<0)ss=-ss;
                dd = ts[k].t-ss; if (dd<0) dd=-dd;
                if (dd<ts[k].d) { ts[k].d=dd; ts[k].si=tempv[h].i; ts[k].ei=i; ts[k].s=ss; }
                if (h>0) {
                    h--;
                    ss = temps[i]+tempv[h].v; if (ss<0)ss=-ss;
                    dd = ts[k].t-ss; if (dd<0) dd=-dd;
                    if (dd<ts[k].d) { ts[k].d=dd; ts[k].si=tempv[h].i; ts[k].ei=i; ts[k].s=ss;}
                }
            }

        }
    }
}

int main() {
    int n, k, i, v, si, ei, d, md, t;
    while(1) {
        scanf("%d %d", &n, &k);
        if (n==0 && k==0) break;
        for (i=1; i<=n; i++) scanf("%d", &vs[i]);
        for (i=0; i<k; i++) {
            scanf("%d", &ts[i].t);
            ts[i].d = INF;
        }
        gk=k;
        count(1, n);
        for (i=0; i<k; i++) printf("%d %d %d\n", ts[i].s, ts[i].si, ts[i].ei);
    }
    return 0;
}
