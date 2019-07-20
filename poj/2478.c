#include<stdio.h>
#include<string.h>

#define MAX 1000000
char map[1024*500];
int pm[130000];
int pmc;
long long vs[MAX+1];

void build() {
    memset(map, 0, sizeof(map));
    pmc = 0;
    int t,v,p;
    int i, j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        pm[pmc++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    for (i=2; i<=MAX; i++) {
        vs[i] = i;
    }
    for (i=0; i<pmc; i++) {
        p = pm[i];
        for (j=p; j<=MAX; j+=p) {
            vs[j] /= p; vs[j] *= (p-1);
        }
    }
    for (i=2; i<=MAX; i++) {
        if (vs[i] == i) {
            vs[i] = i-1;
        }
    }
    for (i=3; i<=MAX; i++) {
        vs[i] += vs[i-1];
    }
    
}

int main() {
    build();
    int n; while(1) {
        scanf("%d", &n);
        if (n==0) break;
        printf("%lld\n", vs[n]);
    }
    return 0;
}
