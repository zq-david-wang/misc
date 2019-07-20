#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct {int x, y;}cp[500];
typedef struct {int x, y1, y2, v; }SNode;
SNode sp[1000];

int mycmp(const void* a, const void*b) {
    const SNode* pa = (const SNode*)a;
    const SNode* pb = (const SNode*)b;
    if (pa->x != pb->x) return pa->x-pb->x;
    return pa->v-pb->v;
}

int seg[16384*2];
int smax[16384*2];

void addseg(int s, int y1, int y2, int v, int d) {
    int ty;
    if (y1==0 && y2==d-1) {
        seg[s]+=v;
        smax[s]+=v;
        return;
    }
    d /= 2;
    if (y1<d) {
        ty = y2; if (ty>=d) ty = d-1;
        addseg(s*2+1, y1, ty, v, d);
    }
    if (y2>=d) {
        ty = y1; if (ty<d) ty = d;
        addseg(s*2+2, ty-d, y2-d, v, d);
    }
    ty = smax[s*2+1];
    if (ty<smax[s*2+2]) ty = smax[s*2+2];
    smax[s] = ty + seg[s];
}
int verify(int m, int c, int n) {
    int i, x, y1, y2, j;
    for (i=0; i<n; i++) {
        x = cp[i].x-m+1; if (x<1) x = 1;
        y1 = cp[i].y-m+1; if (y1<1) y1 = 1;
        y2 = cp[i].y;
        j=i*2; sp[j].x = x; sp[j].y1 = y1; sp[j].y2 = y2; sp[j].v = 1;
        j=i*2+1; sp[j].x = cp[i].x+1; sp[j].y1 = y1; sp[j].y2 = y2; sp[j].v = -1;
    }
    qsort(sp, n+n, sizeof(sp[0]), mycmp);
    memset(seg, 0, sizeof(seg));
    memset(smax, 0, sizeof(smax));
    for (i=0; i<n+n; i++) {
        addseg(0, sp[i].y1, sp[i].y2, sp[i].v, 16384);
        if (smax[0]>=c) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int c, n, i;
    scanf("%d %d", &c, &n);
    for (i=0; i<n; i++) scanf("%d %d", &cp[i].x, &cp[i].y);
    int l, h, m;
    l = 0; h = 10000;
    while(l<=h) {
        m = (l+h)/2;
        i = verify(m, c, n);
        if (i) h = m-1;
        else l = m+1;
    }
    while (verify(m, c, n)==0) m += 1;
    printf("%d\n", m);
    return 0;
}
