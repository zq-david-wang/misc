#include<stdio.h>

int cn[100000];
int main() {
    int n, f, i, j, k;
    scanf("%d %d", &n, &f);
    for (i=0; i<n; i++) scanf("%d", &cn[i]); 
    int ss=0, sn=0;
    for (i=0; i<f; i++) { ss += cn[i]; sn++; }
    long long ms=ss, mn=sn;
    long long  sss=0, ssn=0, mss, msn=0;
    int si = 0, mi;
    for (;i<n; i++) {
        sn++; ss += cn[i];
        // update ms, mn
        if (ms*sn<ss*mn) { ms=ss; mn=sn; }
        sss+=cn[i-f];
        ssn++;
        if (msn==0) { 
            msn = ssn; mss = sss; mi = i-f;
        } else {
            if (mss*ssn>sss*msn) { mss = sss; msn = ssn; mi = i-f; }
        }
        if (mss*sn<=ss*msn) {
            for (;si<=mi; si++) { sn--; ss -= cn[si]; }
            msn = 0; mss = 0; sss=0; ssn = 0;
            for (k=si; k+f<=i; k++) {
                ssn++; sss+=cn[k];
                if (msn==0) {
                    msn = ssn; mss = sss; mi = k;
                } else {
                    if (mss*ssn>sss*msn) { mss = sss; msn = ssn; mi = k; }
                }
                if (sss*sn<=ss*ssn) {
                    for (;si<=k; si++) { sn--; ss-=cn[si];}
                    ssn=0; sss=0; msn=0; mss=0;
                }
            }
            if (ms*sn<ss*mn) { ms=ss; mn=sn; }
        }
    }
    for (; si+f<n; si++) {
        sn--; ss-=cn[si];
        if (ms*sn<ss*mn) { ms=ss; mn=sn; }
    }
    printf("%lld\n",  1000*ms/mn);
    return 0;
}
