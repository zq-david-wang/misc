#include<stdio.h>

typedef struct { int x, y; } Point;
Point ups[5004], downs[5004];
int cs[5004];

int ori(Point p1, Point p2, Point p3)
{
    int val = (p2.y - p1.y) * (p3.x - p2.x) -
              (p2.x - p1.x) * (p3.y - p2.y);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int main() {
    int n, m, i, x1, y1, x2, y2, x, y;
    Point cp;
    int l, h, mi, ic=0;
    while(1) {
        scanf("%d", &n); if (n==0) break; ic++;
        scanf("%d %d %d %d %d", &m, &x1, &y1, &x2, &y2);
        ups[0].x=x1; ups[0].y=y1; downs[0].x=x1; downs[0].y=y2;
        ups[n+1].x=x2; ups[n+1].y=y1; downs[n+1].x=x2; downs[n+1].y=y2;
        for (i=1; i<=n; i++) {
            scanf("%d %d", &ups[i].x, &downs[i].x);
            ups[i].y=y1;  downs[i].y=y2;
        }
        for (i=0; i<=n; i++) cs[i]=0;
        for (i=0; i<m; i++) {
            scanf("%d %d", &cp.x, &cp.y);
            l=0; h=n+1;
            while(l+1<h) {
                mi = (l+h)/2;
                if (ori(downs[mi], ups[mi], cp)==1)  l=mi;
                else h=mi;
            }
            cs[l]++;
        }
        if (ic>1) printf("\n");
        for (i=0; i<=n; i++) printf("%d: %d\n", i, cs[i]);

    }
    return 0;
}
