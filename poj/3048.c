#include<stdio.h>

char pmap[400];
int pc;
int primes[400];

void build() {
    pc = 0;
    int i, j;
    for (i=1; i<sizeof(pmap); i++) pmap[i] = 0;
    for (i=2; i<sizeof(pmap); i++) {
        if (pmap[i])continue;
        primes[pc++] = i;
        for (j=i+j; j<sizeof(pmap); j+=i) pmap[j] =1;
    }
}

int main() {
    build();
    int n, mp=0, i, a, ma, oa, cp, p, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &a);
        oa = a;
        cp = 0;
        for (j=0; j<pc; j++) {
            p = primes[j];
            if (p>a) break;
            if ((a%p)==0) cp = p;
            while((a%p)==0) a/=p;
        }
        if (a>cp) cp = a;
        if (mp < cp) {
            mp = cp;
            ma = oa;
        }
    }
    printf("%d\n", ma);
    return 0;
}
