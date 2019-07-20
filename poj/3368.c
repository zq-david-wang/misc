#include<stdio.h>
#include<string.h>

int vs[100000];
int vg[100000];

int gc[100000];
int sg[100000];

int seg[262144];
void addv(int s, int d, int i, int v) {
    if (seg[s]<v) seg[s]=v;
    if (d==1) return;
    d /= 2;
    if (i<d) addv(s*2+1, d, i, v);
    else addv(s*2+2, d, i-d, v);
}

int findm(int s, int d, int i, int j) {
    if (i<0) i=0;
    if (j>=d) j=d-1;
    if (i>j) return 0;
    if (i==0&&j==d-1) return seg[s];
    d /= 2;
    int r = findm(s*2+1, d, i, j);
    int t = findm(s*2+2, d, i-d, j-d); if (r<t) r=t;
    return r;
}

int main() {
    int n, q, i, g, c, md, m, m1;
    int a, b, ga, gb;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        scanf("%d", &q);
        for (i=0; i<n; i++) scanf("%d", &vs[i]);
        g=0; vg[0]=0; c=1; sg[0]=0;
        for (i=1; i<n; i++) {
            if (vs[i]!=vs[i-1]) {
                gc[g++]=c; sg[g]=i; c=1;
            } else c++;
            vg[i]=g;
        }
        gc[g++]=c;
        // printf("group count: %d\n", g);
        // for (i=0; i<g; i++) printf("%d:%d start at %d\n", i, gc[i], sg[i]);
        // for (i=0; i<n; i++) printf("%d:%d\n", i, vg[i]);
        md=1; while(md<g) md*=2;
        memset(seg, 0, sizeof(seg[0])*md*2);
        // printf("md is %d\n", md);
        for (i=0; i<g; i++) addv(0, md, i, gc[i]);
        for(i=0; i<q; i++) {
            scanf("%d %d", &a, &b); a--; b--;
            // printf("process %d->%d\n", a, b);
            ga=vg[a]; gb=vg[b];
            m = 0;
            if (ga+1<=gb-1) m = findm(0, md, ga+1, gb-1);
            // printf("ga: %d, gb: %d, m is %d\n", ga, gb, m);
            if (ga==gb) m=b-a+1;
            else {
                m1 = gc[ga]-(a-sg[ga]); if (m<m1) m=m1;
                m1 = b-sg[gb]+1; if (m<m1) m=m1;
            }
            printf("%d\n", m);
        }
    }
    return 0;
}
