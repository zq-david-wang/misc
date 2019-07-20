#include<stdio.h>
int gcd(int a, int b) {
    int t;
    while(a!=0) {
        t = a;
        a = b%a;
        b = t;
    }
    return b;
}
int main() {
    int n, d;
    int a, b, i, g;
    int mn, md;
    long long dn, dd=-1, cn, cd;
    scanf("%d %d", &n, &d);
    for (i=1; i<=32767; i++) {
        b = i;
        a = (n*b-1)/d;
        if (n*b!=d*a) {
            cn = a*d-b*n;
            if (cn<0) cn=-cn;
            cd = b*d;
            if (dd==-1 || (cn*dd)<(cd*dn)) { dn=cn; dd=cd; mn=a; md=b;}
        }
        a++;
        if (a<b && n*b!=d*a) {
            cn = a*d-b*n;
            if (cn<0) cn=-cn;
            cd = b*d;
            if (dd==-1 || (cn*dd)<(cd*dn)) { dn=cn; dd=cd; mn=a; md=b;}
        }
    }
    printf("%d %d\n", mn, md);
    return 0;
}
