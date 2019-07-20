#include<stdio.h>
#include<stdlib.h>

long long *xs, *ys;
int main() {
    int n, i;
    int xn=10000, yn=10000;
    xs = (long long *)malloc(xn*sizeof(long long));
    ys = (long long *)malloc(yn*sizeof(long long));
    long long lv, tv;
    double x, y, rx, ry;
    while(scanf("%d", &n)==1) {
        printf("%d", n);
        if (n>xn) {
            while(n>xn) xn*=2;
            free(xs); free(ys);
            xs = (long long *)malloc(xn*sizeof(long long));
            ys = (long long *)malloc(yn*sizeof(long long));
        }
        for (i=0; i<n; i++) scanf("%lld %lld", &xs[i], &ys[i]);
        lv = 0; for (i=0; i<n; i++) {
            tv = lv; lv = 2*xs[i]-lv; xs[i]=tv;
        } rx =  lv; rx /= 2;
        lv = 0; for (i=0; i<n; i++) {
            tv = lv; lv = 2*ys[i]-lv; ys[i]=tv;
        } ry = lv; ry /= 2;
        for (i=0; i<n; i++) {
            if (i&1) { 
                x=xs[i]-rx; y=ys[i]-ry;
            } else {
                x = xs[i]+rx; y = ys[i]+ry;
            }
            printf(" %.6f %.6f", x, y);
        } printf("\n");
    }
    return 0;
}
