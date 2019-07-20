#include<stdio.h>
#include<math.h>

struct {double s, e;}seg[100];
int sgc;
int main() {
    int n, x1, x2, y1, y2, x0, y0, r;
    long long t, a, b, c, d;
    int v1, v2, j, i, usex;
    double cv1, cv2, td, s, e, cc;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        scanf("%d %d %d %d", &x1,&y1, &x2,&y2);
        usex=1; v1=x1; v2=x2; if (x1==x2) { usex=0; v1=y1; v2=y2; }
        if (v1>v2) { t=v1; v1=v2; v2=t; }
        sgc=0;
        for (i=0; i<n; i++) { 
            scanf("%d %d %d", &x0, &y0, &r);
            if (usex) {
                t = (x1-x2)*(y1-y0)-(y1-y2)*x1;
                a = (y1-y2)*(y1-y2)+(x1-x2)*(x1-x2);
                b = 2*(y1-y2)*t-2*(x1-x2)*(x1-x2)*x0;
                c = t*t+(x1-x2)*(x1-x2)*x0*x0-r*r*(x1-x2)*(x1-x2);
            } else {
                t = (y1-y2)*(x1-x0)-(x1-x2)*y1;
                a = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                b = 2*(x1-x2)*t-2*(y1-y2)*(y1-y2)*y0;
                c = t*t+(y1-y2)*(y1-y2)*y0*y0-r*r*(y1-y2)*(y1-y2);
            }
            d = b*b-4*a*c;
            if (d<=0) continue;
            td = sqrt(d);
            cv1 = (-b-td)/a/2; 
            cv2 = (-b+td)/a/2; 
            if (cv1>v2||cv2<v1) continue;
            if (cv1<v1) cv1=v1; if (cv2>v2) cv2=v2;
            // printf("%d: %.3f %.3f(%d,%d)\n", i, cv1, cv2, v1, v2);
            for (j=sgc-1; j>=0; j--) {
                if (seg[j].s <= cv1) break;
                seg[j+1]=seg[j];
            }
            seg[j+1].s=cv1; seg[j+1].e=cv2; sgc++;
        }
        s=v1; e=s; cc=0;
        for (i=0; i<sgc; i++) {
            if (seg[i].s>e) {
                cc+=(e-s);
                s = seg[i].s; e = seg[i].e;
            } else { if (e<seg[i].e) e=seg[i].e; }
        }
        cc += (e-s);
        printf("%.2f\n", cc*100/(v2-v1));
    }
    return 0;
}
