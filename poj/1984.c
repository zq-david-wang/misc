#include<stdio.h>

struct {
    unsigned short s, e, l, d;
} memo[40001];
struct {
    unsigned short s, e, i;
} query[10000];
struct {
    int x, y, g, c;
} groups[20001];
struct {
    int x, y, g;
} farms[40001];

char *dirs="NESW";
char scale[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int temp[20000];
int getgid(int g) {
    int ng=g, c=0;
    while (g>=0) {
        ng = groups[g].g;
        if (ng<0) break;
        temp[c++] = g;
        g = ng;
    }
    temp[c] = g;
    c--;
    while(c>=0) {
        groups[temp[c]].g = g;
        groups[temp[c]].x += groups[temp[c+1]].x;
        groups[temp[c]].y += groups[temp[c+1]].y;
        c--;
    }
    return g;
}
int main() {
    int n, m, k, i, j;
    int s, e, l, d;
    int dx, dy, f1, f2;
    int g1, g2, gid, li;
    char c;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) farms[i].g = -1;
    for (i=0; i<m; i++) {
        scanf("%d %d %d %c", &s, &e, &l, &c);
        memo[i].s = s;
        memo[i].e = e;
        memo[i].l = l;
        for (d=0; d<4; d++) if (dirs[d]==c) break;
        memo[i].d = d;
    }
    scanf("%d", &k);
    for (i=0; i<k; i++) {
        scanf("%d %d %d", &s, &e, &j);
        query[i].s = s;
        query[i].e = e;
        query[i].i = j-1;
    }
    gid = 0;
    li = 0;
    for (i=0; i<k; i++) {
        s = query[i].i;
        // collect
        for (j=li; j<=s; j++) {
            f1 = memo[j].s; f2 = memo[j].e; l = memo[j].l; d = memo[j].d;
            // printf("memo %d->%d length: %d, dir %d\n", f1, f2, l, d);
            g1 = getgid(farms[f1].g); g2 = getgid(farms[f2].g);
            if (g1<0 && g2<0) {
                groups[gid].x = 0; groups[gid].y = 0;
                groups[gid].c = 2; groups[gid].g = -1;
                farms[f1].x = 0; farms[f1].y = 0;
                farms[f1].g = gid;
                farms[f2].x = 0+l*scale[d][0]; farms[f2].y = 0+l*scale[d][1];
                farms[f2].g = gid++;
                // printf("new group: %d, dx,dy -> %d,%d\n", gid, farms[f2].x, farms[f2].y);
            } else if (g1<0) {
                farms[f1].x = farms[f2].x-l*scale[d][0];
                farms[f1].y = farms[f2].y-l*scale[d][1];
                farms[f1].g = g2;
                groups[g2].c++;
                // printf("add new point %d,%d to group: %d\n", farms[f1].x, farms[f1].y, g2);
            } else if (g2<0) {
                farms[f2].x = farms[f1].x+l*scale[d][0];
                farms[f2].y = farms[f1].y+l*scale[d][1];
                farms[f2].g = g1;
                groups[g1].c++;
                // printf("add new point %d,%d to group: %d\n", farms[f2].x, farms[f2].y, g1);
            } else {
                if (g1 != g2) {
                    // g1.x + f1.x + lx = dx + g2.x + f2.x
                    // printf("merge group %d(%d,%d),%d(%d,%d)\n", g1, groups[g1].x, groups[g1].y, g2, groups[g2].x, groups[g2].y);
                    dx = groups[farms[f1].g].x+farms[f1].x+l*scale[d][0]-groups[farms[f2].g].x-farms[f2].x;
                    dy = groups[farms[f1].g].y+farms[f1].y+l*scale[d][1]-groups[farms[f2].g].y-farms[f2].y;
                    if (groups[g1].c > groups[g2].c) {
                        groups[g2].g = g1;
                        groups[g2].x = dx;
                        groups[g2].y = dy;
                        groups[g1].c += groups[g2].c;
                    } else {
                        groups[g1].g = g2;
                        groups[g1].x = -dx;
                        groups[g1].y = -dy;
                        groups[g2].c += groups[g1].c;
                    }
                    // printf("after merge group %d(%d,%d),%d(%d,%d)\n", g1, groups[g1].x, groups[g1].y, g2, groups[g2].x, groups[g2].y);
                }
            }
        }
        li = s+1;
        // query
        f1 = query[i].s;
        f2 = query[i].e;
        if (f1==f2) { printf("0\n"); continue; }
        g1 = getgid(farms[f1].g);
        g2 = getgid(farms[f2].g);
        if (g1==-1 || g2==-1 || g1 != g2) printf("-1\n");
        else {
            dx = farms[f1].x+groups[farms[f1].g].x-farms[f2].x-groups[farms[f2].g].x;
            if (dx<0) dx = -dx;
            dy = farms[f1].y+groups[farms[f1].g].y-farms[f2].y-groups[farms[f2].g].y;
            if (dy<0) dy = -dy;
            // printf("farm %d(%d) (%d,%d)+(%d,%d)\n", f1, g1, farms[f1].x, farms[f1].y, groups[g1].x, groups[g1].y);
            // printf("farm %d(%d) (%d,%d)+(%d,%d)\n", f2, g2, farms[f2].x, farms[f2].y, groups[g2].x, groups[g2].y);
            printf("%d\n", dx+dy);
        }
    }
    return 0;
}
