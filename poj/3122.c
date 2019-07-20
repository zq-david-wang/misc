#include<stdio.h>
#include<stdlib.h>
#include<string.h>


long long rs[10000];
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230
int main() {
    int tc, ti, i, n, f;
    long long s, h, l, m, c;
    double r;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &n, &f);
        s=0;
        for (i=0; i<n; i++) {
            scanf("%lld", &rs[i]); rs[i]=rs[i]*rs[i]*1000000;
            s += rs[i];
        }
        f++;
        h = s/f+1;
        l = 0;
        while(l<=h) {
            m  = (l+h)/2;
            c=0;
            for (i=0; i<n; i++) {
                c += rs[i]/m;
                if (c>=f) break;
            }
            if (c>=f) { if (l==m) break; l=m; }
            else h=m-1;
        }
        m=l+1; c=0; for (i=0; i<n; i++) { c+=rs[i]/m; if (c>=f) break; } if (c>=f) l++;
        r = l; r/=1000000; r*=PI;
        printf("%.6f\n", r);

    }
    return 0;
}


