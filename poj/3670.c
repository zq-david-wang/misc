#include<stdio.h>

int cs2[30001], mx[30001], ms[30001];
int main() {
    int n, i, c, mc, c1, c2, c3, msc, nc;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &ms[i]);
    c2 = 0; cs2[n] = 0; msc=0; c3=0;
    for (i=n-1; i>=0; i--) {
        if (ms[i]!=2) c2++;    
        cs2[i] = c2;
        if (ms[i]!=3) c3++;
        c1 = c3-c2;
        if (c1<msc)msc=c1;
        mx[i] = msc;
    }
    c = 0; mc = n;
    for (i=0; i<n; i++) {
        nc = c+cs2[i]+mx[i];
        if (nc<mc) mc = nc;
        if (ms[i]!=1) c++;
    }
    if (c<mc) mc = c;
    // 3
    c2 = 0; cs2[n] = 0; msc=0; c1=0;
    for (i=n-1; i>=0; i--) {
        if (ms[i]!=2) c2++;    
        cs2[i] = c2;
        if (ms[i]!=1) c1++;
        c3 = c1-c2;
        if (c3<msc)msc=c3;
        mx[i] = msc;
    }
    c = 0; mc = n;
    for (i=0; i<n; i++) {
        nc = c+cs2[i]+mx[i];
        if (nc<mc) mc = nc;
        if (ms[i]!=3) c++;
    }
    if (c<mc) mc = c;
    printf("%d\n", mc);
    return 0;
}
