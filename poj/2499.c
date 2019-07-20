#include<stdio.h>

int main() {
    int n, i, a, b, rc, lc;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        printf("Scenario #%d:\n", i);
        scanf("%d %d", &a, &b);
        lc = 0; rc = 0;
        while(a != 1 && b != 1) {
            if (a>b) {
                lc += a/b;
                a %= b;
            } else {
                rc += b/a;
                b %= a;
            }
        }
        lc += (a-1); rc += (b-1);
        printf("%d %d\n", lc, rc);
        printf("\n");
    }
    return 0;
}
