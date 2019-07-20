#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MOD 100000
#define MAX 10000
unsigned int queue[MOD];
int  gcd(int a, int b) {
    int t; while(a) {
        t=a; a=b%a; b=t;
    }
    return b;
}
int cogs[32];
int primes[] = {2,3,5,7,11,13,17,19};
char cf[32];
#define FACTOR 1600
char flag[MAX*FACTOR];

int main() {
    int tc, ti, n, i, m, a, b, j, v, k, c;
    int ca, cb, g;
    int min, r, ii, f;
    int cgs[32], head, tail;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        scanf("%d", &n);
        min = MAX; 
        for (i=0; i<n; i++) {
            scanf("%d", &cogs[i]);
            if (min>cogs[i]) min=cogs[i];
        }
        for (i=0; i<=20; i++) cf[i]=0;
        for (i=0; i<n; i++) { cogs[i]/=min; cf[cogs[i]]=1; }
        k=0; for (i=0; i<n; i++) {
            if (cogs[i]==1) continue;
            if (cogs[i]==11||cogs[i]==13||cogs[i]==17||cogs[i]==19) continue;
            cgs[k++] = cogs[i];
        }
        memset(flag, 0, sizeof(flag));
        head=tail=0; queue[head++] = 1; flag[1]=1;
        while(tail!=head) {
            v = queue[tail++]; tail %=MOD;
            for (i=0; i<k; i++) {
                j = v*cgs[i];
                if (j>=sizeof(flag)) continue;
                if (flag[j]) continue;
                flag[j]=1;
                queue[head++]=j; head %=MOD;
            }
        }
        scanf("%d", &m);
        if (ti>1) printf("\n");
        printf("Scenario #%d:\n", ti);
        for (i=0; i<m; i++) {
            scanf("%d %d", &a, &b);
            g=gcd(a, b); ca = a/g; cb=b/g;
            for (j=4; j<8; j++) {
                if ((ca%primes[j])==0 || (cb%primes[j])==0) {
                    if (cf[primes[j]]) break;
                }
                if ((ca%primes[j])==0) ca/=primes[j];
                if ((cb%primes[j])==0) cb/=primes[j];
            }
            if (j<8) {
                printf("Gear ratio %d:%d cannot be realized.\n", a, b);
                continue;
            }
            for (j=1; j<=FACTOR; j++) {
                if (flag[j*ca]&&flag[j*cb]) break;
            }
            if (j<=FACTOR) printf("Gear ratio %d:%d can be realized.\n", a, b);
            else printf("Gear ratio %d:%d cannot be realized.\n", a, b);
        }
    }
    return 0;
}


