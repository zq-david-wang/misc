#include<stdio.h>

char vs[128];
int main() {
    int n, i, r, ic=0;
    int cs[12];
    char a[4], b[4], c[4], va, vb, vc;
    int wc, my, dealer;
    double rv;
    for (i='1'; i<='9'; i++) vs[i]=i-'0';
    vs['T'] = 10; vs['K'] = 10;
    vs['Q'] = 10; vs['J'] = 10;
    vs['A'] = 11;
    while(1) {
        scanf("%d", &n); if (n==0) break; ic++;
        for (i=1; i<10; i++) cs[i]=n*4; cs[i]=n*4*4;  cs[11]=n*4;
        r = n*52-3;
        scanf("%s %s %s", a, b, c);
        va = vs[a[0]]; cs[va]--;
        vb = vs[b[0]]; cs[vb]--;
        vc = vs[c[0]]; cs[vc]--;
        my = vb+vc; if (my>21) my-=10;
        wc = 0;
        for (i=2; i<=11; i++) {
            dealer = va+i; if (dealer>21) dealer-=10;
            if (dealer<my) wc+=cs[i];
        }
        rv = wc*100;  rv /= r;
        if (ic>1) printf("\n");
        printf("%.3f%%\n", rv);
    }
    return 0;
}
