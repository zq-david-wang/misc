#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MOD 100000
unsigned char queue[MOD][2];
#define MAX 10000
int  gcd(int a, int b) {
    int t; while(a) {
        t=a; a=b%a; b=t;
    }
    return b;
}
void assert(char *p) { *p = 0; }
int cogs[32];
int primes[] = {2,3,5,7,11,13,17,19};
char cf[32], ff[32];
char dp[128][128];
#define BASE 64
char ubinds[] = {127, 127, 53, 22 };
char dbinds[] = {0, 0, 10, 10 };
char cans[32][4], as[4], bs[4];
int canc;
int main() {
    int tc, ti, n, i, m, a, b, j, v, k, c, d;
    int ca, cb, g;
    int min, r, ii, f;
    int head, tail;
    int na, nb, nc, nd;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        scanf("%d", &n);
        min = MAX; 
        for (i=0; i<n; i++) {
            scanf("%d", &cogs[i]);
            if (min>cogs[i]) min=cogs[i];
        }
        for (i=0; i<=20; i++) { cf[i]=0;  ff[i]=0; }
        for (i=0; i<n; i++) { cogs[i]/=min; cf[cogs[i]]=1; }
        for (i=0; i<8; i++)  {
            for (j=0; j<n; j++) if ((cogs[j]%primes[i])==0)break;
            if (j<n) ff[i]=1;
        }
        if (cf[7]&&cf[14]) { if (cf[2]==0) {cf[2]=1; cogs[n++] = 2; }}
        if (cf[5]) {
            if (cf[10]&&cf[2]==0) { cf[2]=1; cogs[n++]=2; }
            if (cf[15]&&cf[3]==0) { cf[3]=1; cogs[n++]=3; }
            if (cf[20]&&cf[4]==0) { cf[4]=1; cogs[n++]=4; }
        } else if (cf[10]&&cf[20]&&cf[2]==0) { cf[2]=1;cogs[n++]=2;}

        k=0; for (i=0; i<n; i++) {
            if (cogs[i]==1) continue;
            for (j=2; j<8; j++) if ((cogs[i]%primes[j])==0) break;
            if (j==8) {
                c=0; while((cogs[i]%2)==0) { c++; cogs[i]/=2; } cans[k][0]=c;
                c=0; while((cogs[i]%3)==0) { c++; cogs[i]/=3; } cans[k][1]=c;
                k++;
            }
        }
        if (cf[10]&&cf[15]) { cans[k][0]=1; cans[k][1]=-1; k++;}
        if (cf[15]&&cf[20]) { cans[k][0]=2; cans[k][1]=-1; k++;}
        canc = k;
        memset(dp, 0, sizeof(dp)); dp[BASE][BASE]=1;
        head=tail=0;
        queue[head][0]=BASE; queue[head][1]=BASE; head++;
        while(tail!=head) {
            a=queue[tail][0]; b=queue[tail][1];
            tail++; tail%=MOD;
            for (i=0; i<k; i++) {
                na=a+cans[i][0]; nb=b+cans[i][1];
                if (na<=ubinds[0]&&nb<=ubinds[1]&&na>=dbinds[0]&&nb>=dbinds[1]&&dp[na][nb]==0) {
                    dp[na][nb]=1;
                    queue[head][0]=na; queue[head][1]=nb;
                    head++; head %=MOD;
                }
                na=a-cans[i][0]; nb=b-cans[i][1];
                if (na<=ubinds[0]&&nb<=ubinds[1]&&na>=dbinds[0]&&nb>=dbinds[1]&&dp[na][nb]==0) {
                    dp[na][nb]=1;
                    queue[head][0]=na; queue[head][1]=nb;
                    head++; head %=MOD;
                }
            }
        }
        scanf("%d", &m);
        if (ti>1) printf("\n");
        printf("Scenario #%d:\n", ti);
        for (i=0; i<m; i++) {
            scanf("%d %d", &a, &b);
            g=gcd(a, b); ca = a/g; cb=b/g;
            for (j=0; j<8; j++) {
                if ((ca%primes[j])==0 || (cb%primes[j])==0) {
                    if (ff[j]==0) break;
                }
            }
            if (j<8) {
                printf("Gear ratio %d:%d cannot be realized.\n", a, b);
                continue;
            }
            for (j=0; j<4; j++) {
                c=0; while((ca%primes[j])==0) { c++; ca/=primes[j]; } as[j]=c;
                c=0; while((cb%primes[j])==0) { c++; cb/=primes[j]; } bs[j]=c;
            }
            if (as[3]||bs[3]) {
               if (cf[7]==0) {
                    as[0]-=as[3];
                    bs[0]-=bs[3];
               }
            }
            if (as[2]||bs[2]) {
                if (cf[5]==0) {
                    if (cf[10]) { as[0]-=as[2]; bs[0]-=bs[2]; }
                    else if (cf[15]) { as[1]-=as[2]; bs[1]-=bs[2]; }
                    else if (cf[20]) { as[0]-=(2*as[2]); bs[0]-=(2*bs[2]); }
                    else assert(0);
                }
            }
            na = as[0]-bs[0]+BASE;
            nb = as[1]-bs[1]+BASE;
            if (dp[na][nb]) printf("Gear ratio %d:%d can be realized.\n", a, b);
            else printf("Gear ratio %d:%d cannot be realized.\n", a, b);
        }
    }
    return 0;
}


