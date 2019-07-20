#include<stdio.h>

#define EPS  0.00001
int main() {
    int b, w, c, i, v1 ,v2, v3;
    double tr, x, cr, d;
    while(1) {
        scanf("%d %d %d", &b, &w, &c); if (b==0) break;
        b *= 16; w*=16;
        tr=b; tr/=w; v1=b*b*c; v2=w*(b-c); v3=b*(w+c);
        x = b; i=0; while(1) {
            i++;
            x = (v1+v2*x)/v3;
            cr = x; cr /= (b-x);
            d = cr-tr; if (d<0) d=-d;
            if (d>=EPS) continue;
            cr = (b-x) / (w-b+x);
            d = cr-tr; if (d<0) d=-d;
            if (d<EPS) break;
        }
        printf("%d\n", i);
    }
    return 0;
}
