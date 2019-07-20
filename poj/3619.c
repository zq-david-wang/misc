#include<stdio.h>

int main() {
    int n, k, i;
    int s, t, r;
    int u, c, re;
    scanf("%d %d", &n, &k);
    for (i=0; i<k; i++) {
        scanf("%d %d %d", &s, &t, &r);
        u = s*t;
        c = (n+u-1)/u;
        re = n - (c-1)*u;
        u = (c-1)*(t+r) + (re+s-1)/s;
        printf("%d\n", u);
    }
    return 0;
}
