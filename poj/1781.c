#include<stdio.h>


int sur(int n) {
    if (n==1) return 0;
    int t = sur(n/2);
    if (n&1) {
        return t*2+2;
    } else {
        return t*2;
    }
}
int main() {
    char b[8];
    int v, n, i;
    while(1) {
        scanf("%s", b);
        if (b[0]=='0'&&b[1]=='0'&&b[3]=='0') break;
        v = (b[0]-'0')*10+b[1]-'0';
        n = b[3]-'0';
        for (i=0; i<n; i++) v*= 10;
        n = sur(v);
        printf("%d\n", n+1);
    }
    return 0;
}
