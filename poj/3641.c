/*
 * =====================================================================================
 *
 *       Filename:  3641.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月18日 12时30分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<string.h>

char pmap[40000];
int primes[10000];
int pmc;
void build() {
    memset(pmap, 0, sizeof(pmap));
    pmc = 0;
    int i, j; for (i=2; i<sizeof(pmap); i++) {
        if (pmap[i]==1) continue;
        for (j=i+i; j<sizeof(pmap); j+=i) {
            pmap[j] = 1;
        }
        primes[pmc++] = i;
    }
}
char isprime(int p) {
   int i; for (i=0; i<pmc; i++) {
       if (p<=primes[i]) break;
       if ((p%primes[i])==0) return 0;
   } 
   return 1;
}
int main() {
    int p,a, n;
    long long v, b;
    build();
    while(1) {
        scanf("%d %d", &p, &a);
        if (p==0 && a==0) break;
        v = 1; 
        if (!isprime(p)) {
            n = p;
            b = a;
            while(n>0) {
                if (n&1) v = (v*b)%p;
                if (v==0) break;
                b = (b*b)%p;
                n>>=1;
            }
        }
        if (v==a) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}

