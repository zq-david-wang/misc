/*
 * =====================================================================================
 *
 *       Filename:  2720.c
 *
 *    Description:  na
 *
 *        Version:  1.0
 *        Created:  2019年06月05日 08时25分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DavidZQWang/lddlinan 00107082@163.com
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int gcd(int a, int b) {
    int t; while(a) { t=a; a=b%a; b=t; }
    return b;
}
int myexp(int b, long long n, int m) {
    long long r=1, bb=b;
    if (n<0) printf("calc wrong exp %d %lld %d\n", b, n, m);
    while(n) {
        if (n&1) { r*=bb; r%=m; }
        n>>=1;
        bb *= bb; bb %= m;
    }
    return r;
}
char mark[10000];
int primes[5120], pc;
int base[10];
int maxvs[101][101];
#define INF 0x7fffffff
int maxv32(int b, int i) {
    if (maxvs[b][i] != -1) return maxvs[b][i];
    int r = maxv32(b, i-1);
    if (r!=INF) {
        long long t = 1; while(r) {
            t*=b; if (t>=INF) break; r--;
        }
        if (t>=INF) r = INF;
        else r=t;
    }
    maxvs[b][i]=r;
    return r;
}
int dp[101][101][16][8];
int p2[16], p5[10];
void build() {
    memset(mark, 0, sizeof(mark));
    memset(maxvs, 0xff, sizeof(maxvs));
    memset(dp, 0xff, sizeof(dp));
    int i, j; pc=0;
    p2[0]=1;for (i=1; i<16; i++) p2[i]=p2[i-1]*2;
    p5[0]=1;for (i=1; i<10; i++) p5[i]=p5[i-1]*5;
    for (i=1; i<=100; i++) maxvs[i][0]=1;
    for (i=1; i<=100; i++) maxvs[i][1]=i;
    for (i=1; i<=100; i++) for (j=2; j<=100; j++) maxv32(i, j);
    base[0]=1;
    for (i=1; i<10; i++) base[i]=10*base[i-1];
    for (i=2; i<sizeof(mark); i++) {
        if (mark[i]) continue;
        primes[pc++] = i;
        for (j=i+i; j<sizeof(mark); j+=i) mark[j]=1;
    }
}
int phi(int n) {
    int i, r=1, c, b, p;
    for (i=0; i<pc; i++) {
        p = primes[i];
        if (p>n) break;
        b=1; c=0; while((n%p)==0) { c++; n/=p; b*=p;}
        if (c==1) r*=(p-1);
        else if (c>1) r*=(b-b/p);
    }
    return r;
}
int calc(int b, int i, int twoc, int fivec);
int mycalc(int g, int a, int b, int m, int i, int nn) {
    int gg = gcd(g, nn);
    int gc=0, bb=g; if (gg>1) { while((bb%gg)==0) {gc++; bb/=gg;} }
    long long t;
    int phn;
    int r1=1; if (bb!=1) { 
        phn=phi(nn); 
        int ntc=0, nfc=0, tn=phn; while((tn%2)==0) {tn/=2; ntc++; }
                while((tn%5)==0) { tn/=5; nfc++; }
        t=calc(m, i, ntc, nfc); t=t*a-b; t%=phn; if (t<0) t+=phn; r1=myexp(bb, t, nn);
    }
    int r2=1; if (gg>1) {
        int nnn=nn, f=1, fc=0; while((nnn%g)==0) { nnn/=gg; f*=gg; fc++;}
        if (nnn==1) {
            t=maxvs[m][i];
            if (a*t<b) printf("something wrong\n");
            if (t==INF|| (t*a-b)*gc>=fc) r2=0;
            else r2 = myexp(gg, (t*a-b)*gc, nn);
        } else {
            // assuming 
            t=maxvs[m][i];
            if (t==INF||(t*gc*a)>(gc*b+fc)) {
                r2 = mycalc(gg, gc*a, gc*b+fc, m, i, nnn);
                r2 *= f;
            } else {
                if (a*t<b) printf("something wrong 2\n");
                r2 = myexp(gg, gc*(a*t-b), nn);
            }
        }
    }
    t=r1; t*=r2; t%=nn; r1=t;
    return r1;
}
int calc(int b, int i, int twoc, int fivec) {
    if (dp[b][i][twoc][fivec]!=-1) return dp[b][i][twoc][fivec];
    int n = p2[twoc]*p5[fivec];
    int v = maxvs[b][i]; if (v!=INF) { 
        dp[b][i][twoc][fivec]=v%n;
        return dp[b][i][twoc][fivec];
    }
    int g = gcd(b, n);
    int gc=0, bb=b; if (g>1) { while((bb%g)==0) {gc++; bb/=g;} }
    int r1=1; if (bb!=1) {
        int ntc=0, nfc=0;
        if (twoc) ntc=twoc-1;
        if (fivec) { ntc+=2;  nfc=fivec-1; }
        r1 = calc(b, i-1, ntc, nfc); r1=myexp(bb, r1, n);
    }
    long long t;
    int r2=1; if (g>1) {
        int nn=n;
        int f=1, fc=0; while((nn%g)==0) { nn/=g; f*=g; fc++;}
        if (nn==1) {
            t=maxvs[b][i-1];
            if (t==INF|| t*gc>=fc) r2=0;
            else r2 = myexp(g, t*gc, n);
        } else {
            t=maxvs[b][i-1];
            if (t==INF||t*gc>fc) {
                r2 = mycalc(g, gc, fc, b, i-1, nn);
                r2 *= f;
            } else {
                r2 = myexp(g, t*gc, n);
            }
        }
    }
    t=r1; t*=r2; t%=n; r1=t;
    // printf("calc %d to %d mod %d ==> %d\n", b, i, n, r1);
    dp[b][i][twoc][fivec] = r1;
    return r1;
}

char format[32];
int main() {
    int b, i, n, ic=0;
    int k, r;
    build();
    while(1) {
        scanf("%d", &b); if (b==0) break; ic++;
        scanf("%d %d", &i, &n);
        // if (1) { printf("process %d %d %d\n", b, i, n); }
        r = calc(b, i, n, n);
        sprintf(format, "%%0%dd\n", n);
        printf(format, r);
    }
    return 0;
}
