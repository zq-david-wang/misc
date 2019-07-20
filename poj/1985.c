#include<stdio.h>
#include<string.h>

typedef struct { unsigned short l, i; }Nei;
Nei map[40001][4];
char flag[40001];
char *dir = "NESW";
int gmax;
int findmax(int r) {
    flag[r] = 1;
    int md[2] = {0, 0};
    int d, ni, m; for (d=0; d<4; d++) {
        ni = map[r][d].i;
        if (ni==0) continue;
        if (flag[ni]) continue;
        m = findmax(ni) + map[r][d].l;
        if(md[1]<m) {
            md[1] = m;
            if (md[0]<md[1]) { m=md[0]; md[0]=md[1];md[1]=m; }
        }
    }
    m = md[0]+md[1];
    if (m>gmax) gmax = m;
    return md[0];
}
int main() {
    int n, m, i;
    int a, b, l;
    char c, d;
    scanf("%d %d", &n, &m);
    memset(flag, 0, sizeof(flag));
    memset(map, 0, sizeof(map));
    for (i=0; i<m; i++) {
        scanf("%d %d %d %c", &a, &b, &l, &c);
        for (d=0; d<4; d++) if (dir[d]==c) break;
        map[a][d].l = l; map[a][d].i = b;
        d = (d+2)%4;
        map[b][d].l = l; map[b][d].i = a;
    }
    gmax = -1;
    findmax(1);
    printf("%d\n", gmax);
    return 0;
}
