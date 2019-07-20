#include<stdio.h>

int main() {
    int a, b, sa=0, ms=0;
    scanf("%d %d", &a, &b);
    while(a) {
        sa += (a%10);
        a /= 10;
    }
    while(b) {
        ms += sa * (b%10);
        b /= 10;
    }
    printf("%d\n", ms);
    return 0;
}
