#include<stdio.h>
#include<stdlib.h>

typedef struct { short x,y; }Point;
Point lps[64], rps[64];
int mycmp(const void *a, const void *b) {
    const Point* pa = (const Point*)a;
    const Point* pb = (const Point*)b;
    if (pa->x==0) {
        if (pb->x==0) { 
            if (pa->y>0&&pb->y>0) return pa->y-pb->y;
            if (pa->y<0&&pb->y<0) return pa->y-pb->y;
            if (pa->y>0) return -1;
            return 1;
        }
        if (pb->y>0) return -1; else return 1;
    } else {
        if (pb->x==0) { if (pb->y<0) return -1; else return 1; }
        return  pa->y*pb->x - pa->x*pb->y;
    }
    return 0;
}
int main() {
    int x, y, ll=0, rl=0, i;
    int cs[4]; cs[0]=cs[1]=cs[2]=cs[3]=0;
    while(scanf("%d %d", &x, &y)==2) {
        if (x==0&&y==0) {}
        else if (x<=0) { lps[ll].x=x; lps[ll].y=y; ll++; }
        else { rps[rl].x=x; rps[rl].y=y; rl++; }
        if (x>0&&y>0) cs[0]++;
        if (x>0&&y<0) cs[1]++;
        if (x<0&&y<0) cs[2]++;
        if (x<0&&y>0) cs[3]++;
    }
    qsort(lps, ll, sizeof(lps[0]), mycmp);
    qsort(rps, rl, sizeof(rps[0]), mycmp);
    printf("(0,0)\n");
    if (cs[0]==0 || cs[3]==0) {
        // from left to right
        for (i=0; i<ll; i++) printf("(%d,%d)\n", lps[i].x, lps[i].y);
        for (i=0; i<rl; i++) printf("(%d,%d)\n", rps[i].x, rps[i].y);
    } else  {
        for (i=0; i<rl; i++) printf("(%d,%d)\n", rps[i].x, rps[i].y);
        for (i=0; i<ll; i++) printf("(%d,%d)\n", lps[i].x, lps[i].y);
    }
    return 0;
}
