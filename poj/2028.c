#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int cs[128];
int main() {
    int n, q, i, j, r, m, c, d;
    while(1) {
        scanf("%d %d", &n, &q); if (n==0&&q==0) break;
        memset(cs, 0, sizeof(cs));
        for (i=0; i<n; i++) {
            scanf("%d", &c);
            for (j=0; j<c; j++) {
                scanf("%d", &d);
                cs[d]++;
            }
        }
        r=0; m=0;
        for (i=1; i<=100; i++) {
            if (cs[i]<q) continue;
            if (cs[i]>m) { m=cs[i]; r=i; }
        }
        printf("%d\n", r);
    }
    return 0;
}


