#include<stdio.h>

int ts[32];
double ms[32];
double rate[32];
#define EPS 0.0000001
int  main() {
    int n, i, ic=0;
    int em;
    double gain, l, h, m, v, d;
    while(1) {
        scanf("%d", &n); if (n==-1) break; ic++;
        for (i=0; i<n; i++) scanf("%d %lf", &ts[i], &ms[i]);
        scanf("%d %lf", &em, &gain);
        l=0; h=1;
        while(l<h) {
            m = (l+h)/2;
            rate[0]=1; for (i=1; i<13; i++) rate[i]=rate[i-1]*(1+m);
            v = 0; for (i=0; i<n; i++) v+=rate[em-ts[i]+1]*ms[i];
            d = v-gain;
            if (d>EPS) h=m;
            else if (d<-EPS) l=m;
            else {
                if (ic>1) printf("\n");
                printf("Case %d: %.5f\n", ic, m);
                break;
            }
        }
            
    }
    return 0;
}
