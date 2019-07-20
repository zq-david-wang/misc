#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int n, i, v, nv;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        scanf("%d", &v); printf("%d", v);
        for (i=1; i<n; i++) {
            scanf("%d", &nv); if (nv==v) continue;
            v=nv; printf(" %d", v);
        }
        printf(" $\n");
    }
    return 0;
}


