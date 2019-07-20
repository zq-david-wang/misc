#include<stdio.h>
#include<string.h>

char map[1000000];
int primes[80000], pc;
char cs[80000];
int ps[80000];
int main() {
    memset(map, 0, sizeof(map)); pc=0;
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        primes[pc++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    memset(cs, 0, sizeof(cs));
    int a, b, c, p, d, s, ti=0; 
    while(1) {
        scanf("%d %d", &a, &b); if (a==0) break; ti++;
        c = 0; d=0;
        for (i=0; i<pc; i++) {
            p = primes[i];
            if (p>a) break;
            while((a%p)==0) { cs[i]++; a/=p; }
            if (cs[i]) ps[c++] = i;
            d += cs[i];
        }
        for (i=0; i<pc; i++) {
            p = primes[i];
            if (p>b) break;
            if (b%p) continue;
            if (cs[i]==0) ps[c++] = i;
            else d -= cs[i];
            s = cs[i];
            while((b%p)==0) { cs[i]++; b/=p; }
            s = cs[i]-s-s;
            if (s<0) s=-s;
            d += s;
        }
        printf("%d. %d:%d\n", ti, c, d);
        for (i=0; i<c; i++) cs[ps[i]]=0;
    }
    return 0;
}
