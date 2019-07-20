#include<stdio.h>

int main() {
    int r, m, y, i;
    double s;
    scanf("%d %d %d", &r, &m, &y);
    s = m;
    for (i=0; i<y; i++) {
        s *= (100+r);
        s /= 100;
    }
    r = s;
    printf("%d\n", r);
    return 0;
}
