#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int zone(int dx, int dy) {
    if (dx==0&&dy==0) printf("error\n");
    if (dy==0) {
        if (dx>0) return 0;
        return 4;
    }
    if (dx==0) {
        if (dy>0) return 2;
        return 6;
    }
    if (dx>0&&dy>0) return 1;
    if (dx<0&&dy>0) return 3;
    if (dx<0&&dy<0) return 5;
    return 7;
}
int mycmp(int dx1, int dy1, int dx2, int dy2) {
    int z1 = zone(dx1, dy1);
    int z2 = zone(dx2, dy2);
    if (z1!=z2) return z1-z2;
    if (z1&1) {
        return dy1*dx2-dy2*dx1; 
    } else return 0;
}
typedef struct { int x, y; } Point;
Point ps1[128], ps2[128];
Point pstack[128];
int stop;
#define max(x,y) (x>y?x:y)
#define min(x,y) (x>y?y:x)
int ori(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
int onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return 1;
    return 0;
}
int doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = ori(p1, q1, p2);
    int o2 = ori(p1, q1, q2);
    int o3 = ori(p2, q2, p1);
    int o4 = ori(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return 1;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;
    return 0; // Doesn't fall in any of the above cases
}

int main() {
    int n, m, i, j, x, y;
    int dx1, dy1, dx2, dy2;
    int sn, sm, o, mi;
    int ci=0;
    Point tp;
    while(1) {
        scanf("%d %d", &n, &m); if (n==0&&m==0) break; ci++;
        for (i=0; i<n; i++) scanf("%d %d", &ps1[i].x, &ps1[i].y);
        for (i=0; i<m; i++) scanf("%d %d", &ps2[i].x, &ps2[i].y);
        if (n==0||m==0||(n==1&&m==1)) { printf("YES\n"); continue; }
        // sort n
        mi=0; for (i=1; i<n; i++) { if (ps1[i].y<ps1[mi].y||(ps1[i].y==ps1[mi].y&&ps1[i].x<ps1[mi].x)) mi=i; }
        if (mi!=0) { tp=ps1[0]; ps1[0]=ps1[mi]; ps1[mi]=tp; } x=ps1[0].x; y=ps1[0].y;
        // for (i=0; i<n; i++) printf("(%d,%d) ", ps1[i].x, ps1[i].y); printf("\n");
        sn=1; for (i=1; i<n; i++) {
            // printf("try insert %d,%d\n", ps1[i].x, ps1[i].y);
            dx1 = ps1[i].x-x; dy1 = ps1[i].y-y;
            for (j=sn-1; j>0; j--) {
                dx2=ps1[j].x-x; dy2=ps1[j].y-y;
                if (mycmp(dx1, dy1, dx2, dy2)==0) {
                    if (dx1*dx1+dy1*dy1>dx2*dx2+dy2*dy2) ps1[j]=ps1[i];
                    break;
                }
            }
            // printf("check duplicating %d\n", j);
            if (j>0) continue;
            tp = ps1[i];
            for (j=sn-1; j>0; j--) {
                dx2=ps1[j].x-x; dy2=ps1[j].y-y;
                if (mycmp(dx2, dy2, dx1, dy1)<=0) break;
                ps1[j+1] = ps1[j];
            } sn++;
            // printf("insert to %d %d,%d\n", j, ps1[i].x, ps1[i].y);
            ps1[j+1]=tp;
        } n=sn;
        // for (i=0; i<n; i++) printf("(%d,%d) ", ps1[i].x, ps1[i].y); printf("\n");
        // sort m
        mi=0; for (i=1; i<m; i++) { if (ps2[i].y<ps2[mi].y||(ps2[i].y==ps2[mi].y&&ps2[i].x<ps2[mi].x)) mi=i; }
        if (mi!=0) { tp=ps2[0]; ps2[0]=ps2[mi]; ps2[mi]=tp; } x=ps2[0].x; y=ps2[0].y;
        sm=1; for (i=1; i<m; i++) {
            dx1 = ps2[i].x-x; dy1 = ps2[i].y-y;
            for (j=sm-1; j>0; j--) {
                dx2=ps2[j].x-x; dy2=ps2[j].y-y;
                if (mycmp(dx1, dy1, dx2, dy2)==0) {
                    if (dx1*dx1+dy1*dy1>dx2*dx2+dy2*dy2) ps2[j]=ps2[i];
                    break;
                }
            }
            if (j>0) continue;
            tp = ps2[i];
            for (j=sm-1; j>0; j--) {
                dx2=ps2[j].x-x; dy2=ps2[j].y-y;
                if (mycmp(dx2, dy2, dx1, dy1)<=0) break;
                ps2[j+1] = ps2[j];
            } sm++;
            ps2[j+1]=tp;
        } m=sm;
        // for (i=0; i<n; i++) printf("(%d,%d) ", ps1[i].x, ps1[i].y); printf("\n");
        // for (i=0; i<m; i++) printf("(%d,%d) ", ps2[i].x, ps2[i].y); printf("\n");
        // printf("n is %d, m is %d\n", n, m);
        if (n==1&&m==2) {
            if (ori(ps2[0], ps2[1], ps1[0])==0) printf("NO\n");
            else printf("YES\n");
            continue;
        }
        if (n==2&&m==1) {
            if (ori(ps1[0], ps1[1], ps2[0])==0) printf("NO\n");
            else printf("YES\n");
            continue;
        }
        if (n==2&&m==2) {
            if (doIntersect(ps1[0], ps1[1], ps2[0], ps2[1])) printf("NO\n"); 
            else printf("YES\n");
            continue;
        }
        if (n>2) {
            pstack[0]=ps1[0];
            pstack[1]=ps1[1];
            pstack[2]=ps1[2]; stop=3;
            for (i=3; i<n; i++) {
                while(ori(pstack[stop-2], pstack[stop-1], ps1[i])!=2) stop--;
                pstack[stop++] = ps1[i];
            }
            for (j=0; j<m; j++) {
                for (i=0; i<stop; i++) {
                    o = ori(pstack[i], pstack[(i+1)%stop], ps2[j]);
                    if (o==1) break;
                }
                if (i==stop) break;
            }
            if (j<m) { printf("NO\n"); continue; }
        }
        if (m>2) {
            pstack[0]=ps2[0]; pstack[1]=ps2[1]; pstack[2]=ps2[2]; stop=3;
            for (i=3; i<m; i++) {
                while(ori(pstack[stop-2], pstack[stop-1], ps2[i])!=2) stop--;
                pstack[stop++] = ps2[i];
            }
            // for (i=0; i<stop; i++) printf("(%d,%d) ", pstack[i].x, pstack[i].y); printf("\n");
            // printf("stop %d\n", stop);
            for (j=0; j<n; j++) {
                for (i=0; i<stop; i++) {
                    o = ori(pstack[i], pstack[(i+1)%stop], ps1[j]);
                    if (o==1) break;
                    // else if (o==0) printf("%d: %d,%d on  edge (%d,%d)->(%d,%d)\n", j, ps1[j].x, ps1[j].y, pstack[i].x, pstack[i].y, pstack[(i+1)%stop].x, pstack[(i+1)%stop].y);
                }
                if (i==stop) break;
            }
            // printf("%d/%d\n", j, n);
            if (j<n) { printf("NO\n"); continue; }
        }
        printf("YES\n");
    }
    return 0;
}


