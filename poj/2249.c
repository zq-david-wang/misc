#include<stdio.h>
#include<string.h>

char map[1024];
int primes[180], pc;
char vmap[1025][180];
void build() {
    pc=0; 
    memset(map, 0, sizeof(map));
    memset(vmap, 0, sizeof(vmap));
    int i, j, k, t; for (i=2; i<sizeof(map); i++) {
        if (map[i]) continue;
        for (k=i; k<=1024; k++) {
            t=k; while((t%i)==0){ vmap[k][pc]++; t/=i; }
        }
        primes[pc++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    // printf("%d\n", pc);
}
int vcs[180];
int main() {
    int n, m, t, i;
    long long v;
    build();
    while(1) {
        scanf("%d %d", &n, &m);
        if (n==0) break;
        t=n-m; if (t<m) m=t;
        if (m==0) printf("1\n");
        else if (n>1024) {
            if (m==1) v=n;
            else if(m==2) { v = n; v*=(n-1); v/=2; }
            if (m==3) {
                v=n; v*=(n-1); v*=(n-2); v/=6;
            }
            printf("%lld\n", v);
        } else {
           for (i=0; i<pc; i++) vcs[i]=0; 
           for (i=0; i<m; i++){
               for (t=0; t<pc; t++) {
                   if (primes[t]>n) break;
                   vcs[t] += vmap[n-i][t];
               }
           }
           // for (i=0; i<pc; i++) { if (primes[i]>n) break; printf("%d: %d ", primes[i], vcs[i]); printf("\n"); }
           for (i=2; i<=m; i++) {
               for (t=0; t<pc; t++) {
                   if (primes[t]>m) break;
                   vcs[t] -= vmap[i][t];
               }
           }
           // for (i=0; i<pc; i++) { if (primes[i]>n) break; printf("%d: %d ", primes[i], vcs[i]); printf("\n"); }
           v = 1; for (i=0; i<pc; i++) while (vcs[i]) { v*=primes[i]; vcs[i]--; }
           printf("%lld\n", v);
        }
    }
    return 0;
}
