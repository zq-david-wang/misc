#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int a, b, c, n, i;
    printf("Gnomes:\n");
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if ((a>=b&&b>=c)||(a<=b&&b<=c)) printf("Ordered\n");
        else printf("Unordered\n");
    }
    return 0;
}


