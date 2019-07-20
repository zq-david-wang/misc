#include<stdio.h>

int ts[100000], ps[25000];
int iis[32];
#define MOD 2147483647
int rs[100000];
int main() {
    int n, k, s, i, j, c=0, lv;
    long long hh, th, ph, d;
    scanf("%d %d %d", &n, &k, &s);
    for (i=0; i<n; i++) {
        scanf("%d", &ts[i]);
    }
    for (i=0; i<k; i++) {
        scanf("%d", &ps[i]);
    }
    // for (i=0; i<n; i++) printf("%d(%d),", ns[i], ts[i]); printf("\n");
    // for (i=0; i<k; i++) printf("%d(%d),", np[i], ps[i]); printf("\n");
    hh = 1;
    for (i=0; i<k-2; i++) {hh *= 3; hh %=MOD;}
    ph = 0;
    for (i=0; i<k-1; i++) {
        ph *= 3;
        if (ps[i+1]>ps[i]) ph += 1;
        else if (ps[i+1]<ps[i]) ph += 2;
        ph %= MOD;
    }
    th = 0;
    for (i=0; i<k-2; i++) {
        th *= 3;
        if (ts[i+1]>ts[i]) th += 1;
        else if (ts[i+1]<ts[i]) th += 2;
        th %= MOD;
    }
    for (;i<n-1; i++) {
        th *= 3;
        if (ts[i+1]>ts[i]) th += 1;
        else if (ts[i+1]<ts[i]) th += 2;
        th %= MOD;
        if (th==ph) {
            //verify i-k+2...i+1
            // printf("verify match %d\n", i-k+2+1);
            j=k;
            if (th!=0) {
                for (j=0; j<32; j++) iis[j] = -1;
                for (j=0; j<k; j++) {
                    if (iis[ps[j]]!=-1 && iis[ps[j]] != ts[i-k+2+j]) break;
                    iis[ps[j]] = ts[i-k+2+j];
                }
                if (j==k) {
                    lv = iis[0];
                    for (j=1; j<32; j++) {
                        if (iis[j] == -1) continue;
                        if (lv>=iis[j]) break;
                        lv = iis[j];
                    }
                    if (j==32) j= k;
                    else j=-1;
                }
            }
            if (j==k) {
                // for (j=0; j<k; j++) printf("%d(%d)-(%d)-", ps[j], ts[i-k+2+j], iis[ps[j]]);printf("\n");
                rs[c++] = i-k+3;
            }
        }
        // remove head
        d = ts[i-k+3] - ts[i-k+2];
        if (d>0) d = 1;
        else if (d<0) d=2;
        d = (d*hh)%MOD;
        th = (th-d+MOD) % MOD;
    }
    printf("%d\n", c);
    for (i=0; i<c; i++) printf("%d\n", rs[i]);

    return 0;
}
