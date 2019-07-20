#include<stdio.h>

#define PI 3.1415926535
int main() {
    int cc, ic;
    int m, n, t, c;
    double a1, a2, a3, a4, at;
    scanf("%d", &cc); for (ic=1; ic<=cc; ic++) {
        if (ic>1) printf("\n"); printf("Case %d:\n", ic);
        scanf("%d %d %d %d", &m, &n, &t, &c);
        a1 = ((double)(t-c))*(t-c)*m*n + ((double)c)/2.0*(t-c)*(m+m+n+n)+1.0*c*c;
        a2 = ((double)c)*(t-c)*((m-2)*(n-1)+(n-2)*(m-1)) + ((double)c)*(t-c/2.0)*((n-1)*2+(m-1)*2);
        a4 = PI*(c/2.0)*(c/2.0)*(m-1)*(n-1);
        at = ((double)m)*n*t*t;
        a3 = at-a1-a2-a4;
        a1 = a1*100/at; a2 = a2*100/at; a3 = a3*100/at; a4 = a4*100/at;
        printf("Probability of covering 1 tile  = %.4f%%\n", a1);
        printf("Probability of covering 2 tiles = %.4f%%\n", a2);
        printf("Probability of covering 3 tiles = %.4f%%\n", a3);
        printf("Probability of covering 4 tiles = %.4f%%\n", a4);
    }
    return 0;
}
