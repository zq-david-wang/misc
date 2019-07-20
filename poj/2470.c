#include<stdio.h>

int perm[100004];
int iperm[100004];
int main() {
    int n, i, v;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=1; i<=n; i++) { 
            scanf("%d", &v);
            perm[i] = v;
            iperm[v] = i;
        }
        for (i=1; i<=n; i++) if (perm[i]!=iperm[i]) break;
        if (i<=n) printf("not ambiguous\n");
        else printf("ambiguous\n");
    }
    return 0;
}
