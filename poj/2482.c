#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int x, y;
    int w, py;
}Star;

Star gstar[10000*2];
int xs[10000];
int ys[10000];
int gmw;
int tree[16384*2+4];
int mtree[16384*2+4];


void panic(char *p) { *p = 0; }
void insert(int i, int s, int e, int w, int n) {
    if (i>=sizeof(tree)/sizeof(tree[0]))panic(0);
    if (s>e) return;
    // if (gmw<tree[i]+w) gmw = tree[i]+w;
    if (s==0 && e==n-1) {
        tree[i] += w;
        mtree[i] += w;
        if (mtree[i]>gmw) gmw = mtree[i];
        return;
    }
    if (e<n/2) insert(i*2+1, s, e, w, n/2);
    else if (s>=n/2) insert(i*2+2, s-n/2, e-n/2, w, n/2);
    else {
        insert(i*2+1, s, n/2-1, w, n/2);
        insert(i*2+2, 0, e-n/2, w, n/2);
    }
    int m1, m2;
    m1 = mtree[i*2+1];
    m2 = mtree[i*2+2];
    if (m1<m2) m1=m2;
    mtree[i] = tree[i]+m1;
    if (mtree[i]>gmw) gmw = mtree[i];
}


int mycmp(const void*a, const void*b) {
    return *((const int*)a) - *((const int*)b);
}
int mycmp2(const void *a, const void *b) {
    const Star* pa = (const Star*)a;
    const Star* pb = (const Star*)b;
    if (pa->x != pb->x) return pa->x-pb->x;
    return pa->w-pb->w;
}

int find(int *p, int v, int  n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (p[m]==v) return m;
        if (p[m]>v) h = m-1;
        else l = m+1;
    }
    if (p[m]<v) m++;
    return m;
}

int main() {
    int n, w, h, i;
    int px, py, ix, iy;
    int x,y;
    int xn, yn;
    int cn, zn;
    while(scanf("%d %d %d", &n, &w, &h) == 3) {
        if (w<0 || h<0) panic(NULL);
        for (i=0; i<n; i++) {
            scanf("%d %d %d", &x, &y, &gstar[i].w);
            if (x<0||x>0x7fffffff||y<0||y>0x7fffffff) panic(NULL);
            gstar[i].x = x;
            gstar[i].y = y;
            xs[i] = x;
            ys[i] = y;
        }
        if (w==0 || h==0) { printf("0\n"); continue; }
        qsort(xs, n, sizeof(xs[0]), mycmp);
        qsort(ys, n, sizeof(ys[0]), mycmp);
        xn = 0; for (i=0; i<n; i++) {
            if (i>0 && xs[i]==xs[i-1])continue;
            xs[xn++] = xs[i];
        }
        yn = 0; for (i=0; i<n; i++) {
            if (i>0 && ys[i]==ys[i-1])continue;
            ys[yn++] = ys[i];
        }
        // for (i=0; i<xn; i++)printf("%d ", xs[i]);printf("\n");
        // for (i=0; i<yn; i++)printf("%d ", ys[i]);printf("\n");
        cn = n;
        for (i=0; i<n; i++) {
            ix = find(xs, gstar[i].x, xn);
            iy = find(ys, gstar[i].y, yn);
            if (w>gstar[i].x) px = 0;
            else px = find(xs, gstar[i].x-w+1, xn);
            if (h>gstar[i].y) py = 0;
            else py = find(ys, gstar[i].y-h+1, yn);
            // verify
            // if (xs[px]+w <= xs[ix])printf("error1 : %d, %d\n", px, ix);
            // if (ys[py]+h <= ys[iy])printf("error2\n");
            // if (xs[ix] != gstar[i].x || ys[iy] != gstar[i].y) printf("error3\n");
            // if (px>0 && xs[px-1]+w > xs[ix])printf("error4\n");
            // if (py>0 && ys[py-1]+h > ys[iy])printf("error5\n");
            gstar[i].x = ix+1;
            gstar[i].py = py;
            gstar[i].y = iy;
            gstar[cn].x = px;
            gstar[cn].py = py;
            gstar[cn].y = iy;
            gstar[cn].w = gstar[i].w;
            gstar[i].w = -gstar[i].w;
            cn++;
        }
        qsort(gstar, cn, sizeof(gstar[0]), mycmp2);
        zn = 1; while(zn<=yn) zn *=2;
        memset(tree, 0, zn*2*sizeof(tree[0]));
        memset(mtree, 0, zn*2*sizeof(mtree[0]));
        gmw = 0;
        for (i=0; i<cn; i++) {
            printf("seg %d x:%d, y:[%d,%d] => %d\n", i, xs[gstar[i].x], ys[gstar[i].py], ys[gstar[i].y], gstar[i].w);
            insert(0, gstar[i].py, gstar[i].y, gstar[i].w, zn);
        }
        printf("%d\n", gmw);
    }
    return 0;
}
