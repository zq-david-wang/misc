#include<stdio.h>
#include<string.h>

int gcd(int a, int b) {
    if (b<0) b=-b;
    int t;
    while(a!=0) {
        t = a; a = b%a; b = t;
    }
    return b;
}

int xs[200], ys[200];
char map[4000][4000];
int main() {
    int n, i, j, c=0, dx, dy, g;
    char hm=0, vm=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d %d", &xs[i], &ys[i]);
    memset(map, 0, sizeof(map));
    for (i=0; i<n; i++) for (j=i+1; j<n; j++) {
        dx = xs[i]-xs[j];
        dy = ys[i]-ys[j];
        if (dx==0) {
            if (vm==0) c++;
            vm = 1;
        } else if (dy==0) {
            if (hm==0) c++;
            hm = 1;
        } else {
            if (dx<0) {dx=-dx; dy=-dy;}
            g = gcd(dx, dy);
            dx /= g; dy/=g;
            dx += 2000;
            dy += 2000;
            if (map[dx][dy]==0) {
                c++;
                map[dx][dy] = 1;
            }
        }
    }
    printf("%d\n", c);
    return 0;
}
