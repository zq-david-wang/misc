#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int xs[16], ys[16], ws[16];
int findit(double x, double y,  int n) {
    double d, d1;
    d = (x-xs[0])*(x-xs[0])+(y-ys[0])*(y-ys[0]);
    d = ws[0]/d;
    int i, ri=0;
    for (i=1; i<n; i++) {
        d1 = (x-xs[i])*(x-xs[i])+(y-ys[i])*(y-ys[i]);
        d1 = ws[i]/d1;
        if (d<d1) { d=d1; ri=i; }
    }
    // printf("%f,%f -> %d\n", x, y, ri);
    return ri;
}
int main() {
    int t, r, i, k, nk;
    int x1, y1, x2, y2, s;
    double x, y, sx, sy, d, nx, ny, td, f;
    while(1) {
        scanf("%d", &t); if (t==0) break;
        scanf("%d", &r);
        for(i=0; i<t; i++) { scanf("%d %d %d", &xs[i], &ys[i], &ws[i]); }
        scanf("%d %d", &x1, &y1);
        x=x1; y=y1;
        k = findit(x, y, t);
        s=0;
        printf("(%d,%c)", s, k+'A');
        d = 0;
        for (i=0; i<r; i++) {
            x=x1; y=y1;
            scanf("%d %d", &x2, &y2);
            if (x2==x1) { sx=0; sy=1; }
            else if (y2==y1) { sx=1; sy=0; }
            else {
                f = (y2-y1)*(y2-y1); f /= ((x2-x1)*(x2-x1)); f+=1; sx=sqrt(1/f);
                f = (x2-x1)*(x2-x1); f /= ((y2-y1)*(y2-y1)); f+=1; sy=sqrt(1/f);
            }
            if (x2<x1) sx=-sx; if (y2<y1) sy=-sy;
            // printf("%d,%d->%d,%d  step %f,%f start with %f\n", x1, y1, x2, y2, sx, sy, d);
            td = sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
            if (d>0) {
                x+=d*sx; y+=d*sy;
                nk = findit(x, y, t); s++;
                if (nk!=k) { k=nk; printf(" (%d,%c)", s, k+'A'); }
                td -=d;
            }
            while(td>=1) {
                x += sx; y+=sy; td-=1;
                nk = findit(x, y, t); s++;
                if (nk!=k) { k=nk; printf(" (%d,%c)", s, k+'A'); }
            }
            d = 1-td;
            x1=x2; y1=y2; 
        }
        if (d<=.5) {
            x+=sx; y+=sy;
            nk = findit(x, y, t); s++;
            if (nk!=k) { k=nk; printf(" (%d,%c)", s, k+'A'); }
        }
        printf("\n");
    }
    return 0;
}


