#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int ps[128];
int main() {
    int tc ,ti, i, n, m, k, j, ii, li;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &n, &m);
        for (i=0; i<n; i++) scanf("%d", &ps[i]);
        k=0; i=0; for (j=9; j>=1; j--) {
            li=i;
            for (ii=0; ii<n; ii++) {
                if (ps[i]==j) {
                    k++; if (i==m) break;
                    li = i;
                }
                i++; i%=n;
            }
            i=li;
            if (ii<n) break;
        }
        printf("%d\n", k);
    }

    return 0;
}


