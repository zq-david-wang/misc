#include<stdio.h>
#include<string.h>

int primes[8000];
int pmc;
char map[65536];

void build() {
    memset(map, 0, sizeof(map));
    pmc = 0;
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i] == 1) continue;
        primes[pmc++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j] = 1;
    }
}

int main() {
    build();
    int n, i, p;
    long long v, t, s, tv;
    while(scanf("%d", &n) == 1) {
        v = 1;
        for (i=0; i<pmc; i++) {
            p = primes[i];
            if (n<p) break;
            if (n%p) continue;
            t = 1;
            while((n%p)==0) {
                n/=p;
                t *= p;
            }
            s = t;
            tv = 1;
            while(t>1) {
                t /= p;
                s -= t*tv;
                tv *= p;
                s += t*tv;
            }
            v *= s;
        }
        tv = n; tv += n-1;
        if (n!=1) v *= tv;
        printf("%lld\n", v);
    }
    return 0;
}
