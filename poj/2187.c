#include<stdio.h>
#include<stdlib.h>

typedef struct {int x,y;} Point;

int cw(Point x, Point y, Point z) {
    int d = (y.x-x.x)*(z.y-x.y)-(y.y-x.y)*(z.x-x.x);
    if (d==0) return 0;
    else if (d<0) return -1; // clockwise
    else return 1; // counter clockwise
}

Point points[50000];
int stack[50000];

int mycmp(const void *a, const void *b) {
    const Point* pa = (const Point*)a;
    const Point* pb = (const Point*)b;
    int dx1 = pa->x-points[0].x; 
    int dy1 = pa->y-points[0].y; 
    int dx2 = pb->x-points[0].x; 
    int dy2 = pb->y-points[0].y; 
    if (dx1>0 && dx2<=0) return -1;
    if (dx1<0 && dx2>=0) return 1;
    if (dx1==0 && dx2!=0) { if (dx2>0) return 1; return -1; }
    int d = dy1*dx2 - dy2*dx1;
    if (d>0) return 1;
    if (d<0) return -1;
    if (dx1==0)  return dy1-dy2;
    if (dx1>0) return dx1-dx2;
    return dx2-dx1;
}
int main() {
    int n, i, mx, my, mi, stop, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d %d", &points[i].x, &points[i].y);
    mx = points[0].x;
    my = points[0].y;
    mi = 0;
    for (i=1; i<n; i++) {
        if (points[i].y < my ||(points[i].y==my&&points[i].x<mx)) {
            mx = points[i].x;
            my = points[i].y;
            mi = i;
        }
    }
    mx=points[0].x; points[0].x=points[mi].x;points[mi].x=mx;
    my=points[0].y; points[0].y=points[mi].y;points[mi].y=my;
    qsort(&points[1], n-1, sizeof(Point), mycmp);
    stop = 0;
    for (i=0; i<n; i++) {
        while(stop>1 && cw(points[stack[stop-2]], points[stack[stop-1]], points[i]) <=0) stop--;
        stack[stop++] = i;
    }
    // printf("stop is %d\n", stop);
    int d, td, x1, y1, x2, y2;
    d = 0;
    for (i=0; i<stop; i++) {
        x1 = points[stack[i]].x;
        y1 = points[stack[i]].y;
        for (j=i+1; j<stop; j++) {
            x2 = points[stack[j]].x;
            y2 = points[stack[j]].y;
            td = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
            if (td>d) d=td;
        }
    }
    printf("%d\n", d);
    return 0;
}
