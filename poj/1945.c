#include<stdio.h>
#include<string.h>


#define MAXB 100
int dis[MAXB][40001];
unsigned int queue[100*40000];
#define MOD 4000000
int main() {
    int p, a, b, i, j, k;
    unsigned int v;
    int maxa, maxb;
    int na, ca, cb, t;
    int ary1[2], ary2[2], ary[8];
    scanf("%d", &p);
    maxa = p*2; maxb = MAXB;
    for (i=0; i<MAXB; i++) memset(dis[i], 0xff, p*2*sizeof(dis[0][0]));
    int head=0, tail=0;
    dis[0][1] = 0;
    queue[head++] = 1<<16;
    while(tail!=head) {
        v = queue[tail++]; tail %= MOD;
        a = v>>16; b = v&0xffff;
        if (a==p) break;
        ary1[0] = a; ary1[1] = b;
        ary2[0] = a; ary2[1] = b;
        k = 0;
        for (i=0; i<2; i++) for (j=0; j<2; j++) {
            ary[k++] = ary1[i]+ary2[j];
            ary[k++] = ary1[i]-ary2[j];
        }
        for (i=0; i<k; i++) {
            na = ary[i]; if (na<0) na=-na;
            if (na==p) { dis[b][a]++; break; }
            ca = na; cb = a; if (ca<cb) { t=ca;ca=cb;cb=t; }
            if (ca<maxa && cb<maxb && dis[cb][ca]==-1) {
                dis[cb][ca] = dis[b][a]+1;
                queue[head++] = (ca<<16)|cb; head %= MOD;
            }
            ca = na; cb = b; if (ca<cb) { t=ca;ca=cb;cb=t; }
            if (ca<maxa && cb<maxb && dis[cb][ca]==-1) {
                dis[cb][ca] = dis[b][a]+1;
                queue[head++] = (ca<<16)|cb; head %= MOD;
            }
        }
        if (i<k) break;
    }
    if (na != p && a != p) printf("error, %d,(%d,%d),%d\n", na, a,b, p);
    printf("%d\n", dis[b][a]);
    return 0;
}
