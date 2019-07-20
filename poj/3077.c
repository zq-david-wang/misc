#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int n, i, ti, tc, base, r;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &n);
        base = 10;
        while(1) {
            if (n<=base) break;
            r = ((n%base) >= base/2);
            n = (n/base+r)*base;
            base *=10;
        }
        printf("%d\n", n);
    }
    return 0;
}


