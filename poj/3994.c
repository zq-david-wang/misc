#include<stdio.h>

int main() {
    int n, n1, n2, n3, ti=0, n4;
    while(1) {
        scanf("%d", &n); if (n==0) break; ti++;
        n1 = 3*n;
        if (n1&1) n2 = (n1+1)/2;
        else n2 = n1/2;
        n3 = 3*n2;
        n4 = n3/9;
        if (n1&1) printf("%d. odd %d\n", ti, n4);
        else printf("%d. even %d\n", ti, n4);
    }
    return 0;
}
