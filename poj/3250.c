#include<stdio.h>

int hs[80001];
int hh[80001];
int main() {
    int n, i, ni;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &hs[i]);
    hs[n] = 1000000001;
    long long s = 0;
    for (i=n-1; i>=0; i--) {
        ni = i+1;
        while(hs[i]>hs[ni]) {
            ni = hh[ni];
        }
        hh[i] = ni;
        s += (ni-i-1);
    }
    printf("%lld\n", s);
    return 0;
}
