#include<stdio.h>

int gcd(int a, int b) {
    int t;
    while (a>0) {
        t=a; a=b%a; b=t;
    }
    return b;
}

int main() {
    int a, b, g;
    long long r;
    while(1) {
        scanf("%d %d", &a, &b); if (a==0) break;
        g = gcd(a, b);
        r = a; r*=b; r/=g;
        g = r/a; r/=b; r*=g;
        printf("%lld\n", r);
    }
    return 0;
}
