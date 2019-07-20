#include<stdio.h>
#include<stdlib.h>

typedef struct { int x, y; }Point;
Point ps[1000];
int mycmp(const void *a, const void *b) {
    const Point *pa = (const Point*)a;
    const Point *pb = (const Point*)b;
    if (pa->x != pb->x) return pa->x-pb->x;
    return pa->y-pb->y;
}

int findpoint(int x, int y, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (ps[m].x==x&&ps[m].y==y) return m;
        if (ps[m].x<x||(ps[m].x==x&&ps[m].y<=y)) l=m+1;
        else h = m-1;
    }
    return -1;
}
int main() {
    int n, i, j, c;
    int x, y, dx, dy, m;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) scanf("%d %d", &ps[i].x, &ps[i].y);
        qsort(ps, n, sizeof(ps[0]), mycmp);
        c = 0;
        for (i=0; i<n; i++) for (j=i+1; j<n; j++) {
            dx = ps[j].x-ps[i].x; dy = ps[i].y-ps[j].y;
            x = dy+ps[j].x; y = dx+ps[j].y;
            m = findpoint(x, y, n);
            // printf("start with (%d,%d)-(%d,%d), need %d:(%d,%d)\n", ps[i].x, ps[i].y, ps[j].x, ps[j].y, m, x, y);
            if (m<j) continue;
            dx = x-ps[j].x; dy=ps[j].y-y;
            x = dy+x; y = dx+y;
            m = findpoint(x, y, n);
            // printf("last pint %d: (%d,%d)\n", m, x, y);
            if (m<i) continue;
            c++;
        }
        printf("%d\n", c);
    }
    return 0;
}
