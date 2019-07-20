#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char street[10][16];
char line[128];
int readline(char *b) {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        b[i++] = c;
    }
    b[i]=0;
    return i;
}
#define EPS 0.000001
int spot(double x, double y, double h, double x1, double y1, double h1) {
    int sx, ex, sy, ey, t;
    sx = x;  sy = y; ex = x1;  ey = y1;
    if (sx>ex) { t=sx;sx=ex;ex=t; }
    if (sy>ey) { t=sy;sy=ey;ey=t; }
    int i, j;
    double tx, ty, dx, dy;
    dx = x-x1; if (dx<0) dx=-dx;
    dy = y-y1; if (dy<0) dy=-dy;
    // line: (Y-y) = (y-y1)/(x-x1)*(X-x)
    for (i=sx; i<ex; i++) for (j=sy; j<ey; j++) {
        if (street[i][j]<=h) continue;
        if (dx<EPS) {
            if (x>=i&&x<=(i+1)) {

            }
        }
       // i,j -> i+1,j 
       tx = (j-y)*(x-x1)/(y-y1);
       // x,y -> x,y+1
       // x+1,y -> x+1,y+1
       // x,y+1 -> x+1,y+1
    }
}
int main() {
    int tc, ti, i, j;
    double x, y, h;
    double x1, y1, h1;
    double x2, y2, h2;
    double x3, y3, h3;
    readline(line);
    sscanf(line, "%d", &tc); for (ti=1; ti<=tc; ti++) {
        printf("Fragfest City #%d\n", ti);
        for (i=0; i<10; i++) {
            readline(street[i]);
            for (j=0; j<10; j++) street[i][j] -= '0';
        }
        j = readline(line);
        for (i=0; i<j; i++) if (line[i]=='('||line[i]==')'||line[i]==',') line[i]=' ';
        sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                &x, &y, &h,
                &x1, &y1, &h1,
                &x2, &y2, &h2,
                &x3, &y3, &h3);
        if (spot(x, y, h, x1, y1, h1)) printf("Player A is in sight\n"); else printf("Player A is hiding\n");
        if (spot(x, y, h, x2, y2, h2)) printf("Player B is in sight\n"); else printf("Player B is hiding\n");
        if (spot(x, y, h, x3, y3, h3)) printf("Player C is in sight\n"); else printf("Player C is hiding\n");
    }
    return 0;
}


