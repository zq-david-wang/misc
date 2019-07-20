#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 131072
typedef struct {
    int s, e, i, si;
}Bar;
Bar bars[100000];
Bar bars2[100000];
Bar points[100000*2];
int mc[100000];
int mc2[100000];

int tree[MAX*2];

void add(int s, int x, int v, int n) {
    // if (s>=sizeof(tree)/sizeof(tree[0])) printf("error\n");
    tree[s] +=v;
    if (n==1) return;
    n /= 2;
    if (x>=n) add(s*2+2, x-n, v, n);
    else add(s*2+1, x, v, n);
}

int count(int s, int x1, int x2, int n) {
    if (x1>x2) return 0;
    if (x1==0 && x2==n-1) return tree[s];
    n/=2;
    if (x1>=n) return count(s*2+2, x1-n, x2-n, n);
    else if (x2<n) return count(s*2+1, x1, x2, n);
    else return count(s*2+1, x1, n-1, n) + count(s*2+2, 0, x2-n, n);
}

int mycmp(const void *a, const void *b) {
    const Bar *pa = (const Bar*)a;
    const Bar *pb = (const Bar*)b;
    if (pa->s != pb->s) return pa->s-pb->s;
    return pa->e-pb->e;
}

int mycmp2(const void *a, const void *b) {
    const Bar *pa = (const Bar*)a;
    const Bar *pb = (const Bar*)b;
    if (pa->e != pb->e) return pa->e-pb->e;
    if (pb->s!=pa->s) return pb->s-pa->s;
    return pb->si - pa->si;
}

int main() {
    int n, i, s, e, c;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) {
            scanf("%d %d", &s, &e);
            bars[i].s = s;
            bars[i].e = e;
            bars[i].i = i;
        }
        qsort(bars, n, sizeof(Bar), mycmp);
        // for (i=0; i<n; i++) printf("(%d,%d)", bars[i].s, bars[i].e);printf("\n");
        c=0; for (i=0; i<n; i++) {
            if (i>0 && bars[i].s==bars[i-1].s&&bars[i].e==bars[i-1].e) {
                bars[i].si = c-1;
                bars2[c-1].i++;
                continue;
            }
            bars2[c].s = bars[i].s;
            bars2[c].e = bars[i].e;
            bars2[c].i = 1;
            bars[i].si = c;
            c++;
        }
        for (i=0; i<c; i++) {
            points[i*2].e = bars2[i].s;
            points[i*2].s = bars2[i].s;
            points[i*2].i = i;
            points[i*2].si = bars2[i].i;
            points[i*2+1].e = bars2[i].e;
            points[i*2+1].s = bars2[i].s;
            points[i*2+1].i = i;
            points[i*2+1].si = -bars2[i].i;
        }
        c *= 2;
        qsort(points, c, sizeof(points[0]), mycmp2);
        memset(tree, 0, sizeof(tree));
        for (i=0; i<c; i++) {
            // printf("add %d by %d via %d\n", points[i].s, points[i].si, points[i].e);
            if (points[i].si > 0) add(0, points[i].s, points[i].si, MAX);
            else {
                add(0, points[i].s, points[i].si, MAX);
                mc[points[i].i] = count(0, 0, points[i].s, MAX);
                // printf("----set %d to %d\n", points[i].i, mc[points[i].i]);
            }
        }
        for (i=0; i<n; i++) {
            // printf("[%d---->%d(%d)]\n", bars[i].i, bars[i].si, mc[bars[i].si]);
            mc2[bars[i].i] = mc[bars[i].si];
        }
        for (i=0; i<n; i++) {
            if (i>0) printf(" %d", mc2[i]);
            else printf("%d", mc2[i]);
        }
        printf("\n");
        
    }
    return 0;
}
