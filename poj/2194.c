#include<stdio.h>
#include<math.h>

#define EPS 0.000001
double xs[10], ys[10];
int main() {
    int n, i, j;
    double x1, y1, x2, y2, x, y, t, d, my;
    double a, b, c;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) { 
            scanf("%lf", &t);
            for (j=i-1; j>=0; j--) {
                if (xs[j]<=t) break;
                xs[j+1]=xs[j];
            }
            xs[j+1] = t;
            ys[i]=1;
        }
        for (i=1; i<n; i++) {
            // printf("round %d: ", i); for (j=0; j<n-i; j++) printf(" %.4f,%.4f ", xs[j], ys[j]); printf("\n");
            for (j=1; j<n; j++) {
                x1=xs[j-1]; y1=ys[j-1];
                x2=xs[j]; y2=ys[j];
                a = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                b = -(x1-x2)*(x1-x2)*y1+(y2*y2-y1*y1)*y1-y2*((x1-x2)*(x1-x2)-y1*y1+y2*y2);
                d = x1*x1-x2*x2+y1*y1-y2*y2;
                c = 4*(x1-x2)*(x1-x2) - d*d/4 + x1*(x1-x2)*(x1*x1-x2*x2+y1*y1-y2*y2)-(x1-x2)*(x1-x2)*x1*x1-y1*y1*(x1-x2)*(x1-x2);
                c = -c;
                t = b*b-4*a*c;
                if (t<-EPS) printf("some caculation %.6f is off track\n", t);
                if (t<EPS) { y=-b/a/2; }
                else {
                    t = sqrt(b*b-4*a*c); y=(-b+t)/a/2;
                }
                x = (d-2*(y1-y2)*y)/(x1-x2)/2;
                xs[j-1]=x; ys[j-1]=y;
            }
        }
        printf("%.4f %.4f\n", xs[0], ys[0]);
    }
    return 0;
}
