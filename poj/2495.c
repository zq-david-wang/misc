#include<stdio.h>

int main() {
    int n, i, k;
    int r1, c1, r2, c2;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
       scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
       k = (r1+r2+c1+c2)&1;
       printf("Scenario #%d:\n%d\n\n", i, k);
    }
    return 0;
}

