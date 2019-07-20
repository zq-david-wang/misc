#include<stdio.h>

int main() {
    int n, i;
    long long lx, ly, x, y, fx, fy;
    double cx, cy;
    while(scanf("%d", &n)==1) {
        printf("%d", n);
        scanf("%lld %lld", &lx, &ly); fx=lx; fy=ly;
        for (i=1; i<n; i++) {
            scanf("%lld %lld", &x, &y);
            cx = x+lx; cx/=2;
            cy = y+ly; cy/=2;
            printf(" %.6f %.6f", cx, cy);
            lx=x; ly=y;
        }
        cx = fx+x; cx/=2;
        cy = fy+y; cy/=2;
        printf(" %.6f %.6f\n", cx, cy);
    }
    return 0;
}
