#include<stdio.h>
#include<math.h>

int main() {
    double k, a, d, x, ph;
    int m, n;
    while(1) {
        scanf("%lf %lf %d %d", &k, &a, &m, &n); if (m==0&&n==0) break;
        d = sqrt(k*k+4*k*a*m*n);
        x = (-k+d)/(2*m*n);
        ph = -log10(x*m);
        printf("%.3f\n", ph);
    }
    return 0;
}
