#include<stdio.h>
#include<string.h>

char map[1000000];
int primes[100000];
int pc;
long long stack[32];
int main() {
    memset(map, 0, sizeof(map)); pc=0;
    int i,j, n; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        primes[pc++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    scanf("%d", &n);
    long long ii, iv;
    int stop, p;
    for (i=0; i<32; i++) {
        if (primes[i]>n) break;
        ii=1; ii<<=primes[i]; ii--;
        iv = ii;
        stop=0;
        for (j=0; j<pc; j++) {
            p = primes[j];
            if (p>ii) break;
            while((ii%p)==0) { stack[stop++] = p; ii/=p; }
        }
        if (ii>1) stack[stop++] = ii;
        if (stop>1) {
            printf("%lld", stack[0]);
            for (j=1; j<stop; j++) printf(" * %lld", stack[j]);
            printf(" = %lld = ( 2 ^ %d ) - 1\n", iv, primes[i]);
        }
    }
    return 0;
}
