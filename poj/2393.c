#include<stdio.h>

int main() {
    int n, s, i;
    int c, y;
    long long r = 0;
    int p = -1;
    scanf("%d %d", &n, &s);
    for (i=0; i<n; i++) {
        scanf("%d %d", &c, &y);
        if (p==-1 || p>c) p = c;
        r += p*y;
        p += s;
    }
    printf("%lld\n", r);
    return 0;
}
