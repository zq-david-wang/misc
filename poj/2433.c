#include<stdio.h>

int hs[1002];
int main() {
    int n, k, i, j;
    scanf("%d %d", &n, &k);
    for (i=1; i<=n; i++) {
        scanf("%d", &hs[i]);
    }
    hs[0] = 0; hs[n+1] = 0;
    int pc, li, s, le, mli, mle, mh, mmh, ms;
    int tss = 0;
    while(1) {
        // count peak and keep minimum
        pc = 0;
        li=0; s=0;
        ms = 0x7fffffff;
        for (i=1; i<=n;) {
            if (i==n+1) break;
            while(hs[i]>=hs[i-1]) { i++; }
            if (i>n) le=i;
            else {
                while(i<=n && hs[i]<=hs[i-1]) { i++; }
                if (i>n) le=i;
                else le = i-1;
            }
            pc++;
            // li....le
            mh = hs[li]; if (mh<hs[le])mh=hs[le];
            s = 0;
            for (j=li; j<=le; j++) {
                if (hs[j]>mh) s+= (hs[j]-mh);
            }
            // printf("peek %d-->%d, s %d, mh %d\n", li, le, s, mh);
            if (s<ms) { ms = s; mli = li; mle = le; mmh = mh;}
            li = le;
        }
        // printf("pc is %d\n", pc);
        if (pc<=k) break;
        for (j=mli; j<=mle; j++) if (hs[j]>mmh) hs[j]=mmh;
        tss += ms;
    }
    printf("%d\n", tss);
    return 0;
}
